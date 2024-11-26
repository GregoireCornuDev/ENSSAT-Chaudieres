#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_image.h>
#include "control_panel_gui.h"
#include <control_panel_manager.h>
#include <unistd.h>
#include "../config.h"

#include "control_panel_config.h"

// Fonction pour charger une texture à partir d'un chemin
static SDL_Texture* load_texture(SDL_Renderer *renderer, const char *file_path) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);
    if (!texture) {
        printf("Erreur : Impossible de charger %s. SDL_image : %s\n", file_path, IMG_GetError());
    }

    return texture;
}

void *control_panel_gui_thread(void *arg) {

    printf("Control Panel GUI Thread Started\n");

    ControlPanelGUI *gui = (void*)arg;
    control_panel_gui_init(gui);


    if(DEBUG == true) {
        // Boucle blanche
        int i;
        while(1) {
            i = 0;
            sleep(1);
        }
    }

    float water_average = 0.0;

    int running = 1;
    SDL_Event event;

    while (running) {
        printf("crash ? \n");

        // Lecture du niveau d'eau moyen envoyé par le central manager
        if (read(gui->water_average_gui_pipe[0], &water_average, sizeof(water_average)) == -1) {
            perror("Erreur de lecture dans gui->water_average_gui_pipe \n");
        }
        printf(" GUI water_average : %f\n", water_average);
        fflush(stdout);


        printf("Update de l'écran \n");
        fflush(stdout);

        // Met à jour la valeur de la jauge
         update_gauge(gui->gauge, water_average);

        // Gestion des événements SDL
        while (SDL_PollEvent(&event)) {
            // Si le bouton X est cliqué, fin de la boucle
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Mets à jour l'interface graphique
        control_panel_gui_update(gui);

        // Ajoute un délai pour limiter la charge CPU
        SDL_Delay(16); // ~60 FPS
    }
}

// Initialisation du panneau de contrôle
//ControlPanelGUI *control_panel_gui_init() {
void *control_panel_gui_init(ControlPanelGUI *gui ) {

    //ControlPanelGUI *gui = (ControlPanelGUI*)malloc(sizeof(ControlPanelGUI));

    // Gestion de la fenêtre
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return NULL;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur SDL_image : %s\n", IMG_GetError());
        SDL_Quit();
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow("Panneau de contrôle",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur fenêtre : %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return NULL;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return NULL;
    }

    if (!gui) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        perror("Erreur création GUI");
        return NULL;
    }
    gui->window = window;
    gui->renderer = renderer;
    gui->texture_count = control_panel_image_count;
    gui->textures = malloc(gui->texture_count * sizeof(SDL_Texture *));
    // Initialiser la jauge
    SDL_Color fg = {0, 255, 0, 255}; // Vert
    SDL_Color bg = {50, 50, 50, 255}; // Gris
    gui->gauge = gauge_init(50, 100, 30, 200, fg, bg);


    if (!gui->textures) {
        printf("Erreur : Allocation mémoire échouée pour les textures.\n");
        free(gui);
        return NULL;
    }


    for (int i = 0; i < gui->texture_count; ++i) {
        gui->textures[i] = load_texture(renderer, control_panel_images[i].file_path);
        if (!gui->textures[i]) {
            printf("Erreur lors du chargement de l'image : %s\n", control_panel_images[i].file_path);
        } else {
            printf("Texture chargée : %s\n", control_panel_images[i].file_path);
        }
    }

    printf("Control Panel Manager GUI Initialized\n");
    //return gui;
}

// Afficher les images
void control_panel_gui_render(ControlPanelGUI *gui) {
    if (!gui) return;

    for (int i = 0; i < gui->texture_count; ++i) {
        SDL_RenderCopy(gui->renderer, gui->textures[i], NULL, &control_panel_images[i].rect);
        const char *error = SDL_GetError();
        if (*error) {
            printf("Erreur SDL : %s\n", error);
            SDL_ClearError();
        }
    }

    // Dessiner la jauge
    render_gauge(gui->renderer, gui->gauge);
}

// Mettre à jour la jauge avec la nouvelle valeur
void control_panel_gui_update(ControlPanelGUI *gui) {


    // Efface l'écran
    SDL_RenderClear(gui->renderer);

    if (gui) {
        control_panel_gui_render(gui);  // Re-render le panneau avec les nouvelles données
    }



    // Met à jour l'écran avec le renderer
    SDL_RenderPresent(gui->renderer);

}

// Nettoyage des ressources
void control_panel_gui_destroy(ControlPanelGUI *gui) {
    if (!gui) return;

    // Nettoye les ressources
    for (int i = 0; i < gui->texture_count; ++i) {
        if (gui->textures[i]) {
            SDL_DestroyTexture(gui->textures[i]);
        }
    }
    free(gui->textures);

    SDL_DestroyRenderer(gui->renderer);
    SDL_DestroyWindow(gui->window);
    IMG_Quit();
    SDL_Quit();

    free(gui);
}
