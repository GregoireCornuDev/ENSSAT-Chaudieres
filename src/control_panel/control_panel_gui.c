#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include "control_panel_gui.h"
#include "control_panel_config.h"

// Fonction pour charger une texture à partir d'un chemin
static SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file_path) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);
    if (!texture) {
        printf("Erreur : Impossible de charger %s. SDL_image : %s\n", file_path, IMG_GetError());
    }

    return texture;
}

// Initialisation du panneau de contrôle
ControlPanelGUI *control_panel_gui_init(SDL_Renderer *renderer) {
    ControlPanelGUI *panel = malloc(sizeof(ControlPanelGUI));
    if (!panel) {
        printf("Erreur : Allocation mémoire échouée.\n");
        return NULL;
    }

    panel->renderer = renderer;  // Le renderer est directement passé ici
    panel->texture_count = control_panel_image_count;
    panel->textures = malloc(panel->texture_count * sizeof(SDL_Texture *));

    if (!panel->textures) {
        printf("Erreur : Allocation mémoire échouée pour les textures.\n");
        free(panel);
        return NULL;
    }

    // Charger les textures à partir de la configuration
    for (int i = 0; i < panel->texture_count; ++i) {
        panel->textures[i] = load_texture(renderer, control_panel_images[i].file_path);
        if (!panel->textures[i]) {
            printf("Erreur lors du chargement de l'image %s\n", control_panel_images[i].file_path);
        }
    }

    // Initialiser la jauge
    SDL_Color fg = {0, 255, 0, 255}; // Vert
    SDL_Color bg = {50, 50, 50, 255}; // Gris
    panel->gauge = create_gauge(50, 100, 30, 200, fg, bg);

    return panel;
}

// Afficher les images
void control_panel_gui_render(ControlPanelGUI *panel) {
    if (!panel) return;

    for (int i = 0; i < panel->texture_count; ++i) {
        SDL_RenderCopy(panel->renderer, panel->textures[i], NULL, &control_panel_images[i].rect);
    }

    // Dessiner la jauge
    render_gauge(panel->renderer, &panel->gauge);
}

// Mettre à jour la jauge avec la nouvelle valeur
void update_control_panel(ControlPanelGUI* gui, ControlPanelData* data) {
    if (gui) {
        gui->gauge.value = data->water_average;  // Mettez à jour la jauge avec la moyenne de l'eau
        control_panel_gui_render(gui);  // Re-render le panneau avec les nouvelles données
    }
}

// Nettoyage des ressources
void control_panel_gui_destroy(ControlPanelGUI *panel) {
    if (!panel) return;

    for (int i = 0; i < panel->texture_count; ++i) {
        if (panel->textures[i]) {
            SDL_DestroyTexture(panel->textures[i]);
        }
    }

    free(panel->textures);
    free(panel);
}
