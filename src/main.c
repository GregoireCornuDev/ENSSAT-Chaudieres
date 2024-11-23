#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include "water_tank/thread_water_level.h"
#include "water_tank/water_valve.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "control_panel/control_panel_gui.h"


int pipe_water_level[2]; // Déclaration globale pour utiliser le pipe dans des fichiers externes

extern void *thread_water_level(void *);
extern void *water_level_sensor_hight(void *);

int main()
{
    pthread_t thread_water_level_id, water_level_sensor_hight_id;

    // Créer un pipe
    int result = pipe(pipe_water_level);
    assert(result == 0); // Vérifier le succès de la création du pipe

    // Créer les threads
    result = pthread_create(&thread_water_level_id, NULL, thread_water_level, NULL);
    assert(result == 0); // Vérifier le succès de la création du thread

    // result = pthread_create(&water_level_sensor_hight_id, NULL, water_level_sensor_hight, NULL);
    // assert(result == 0); // Vérifier le succès de la création du thread

    // Attendre la fin des threads
    pthread_join(thread_water_level_id, NULL);
    // pthread_join(water_level_sensor_hight_id, NULL);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur SDL_image : %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Panneau de contrôle",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur fenêtre : %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }


    // Initialiser le panneau de contrôle
    ControlPanelGUI *panel = control_panel_gui_init(renderer);
    if (!panel) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Boucle principale
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);
        control_panel_gui_render(panel); // Afficher les images
        SDL_RenderPresent(renderer);
    }

    // Nettoyer les ressources
    control_panel_gui_destroy(panel);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}


