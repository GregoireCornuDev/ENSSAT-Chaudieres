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

    panel->renderer = renderer;
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

    return panel;
}

// Afficher les images
void control_panel_gui_render(ControlPanelGUI *panel) {
    if (!panel) return;

    for (int i = 0; i < panel->texture_count; ++i) {
        SDL_RenderCopy(panel->renderer, panel->textures[i], NULL, &control_panel_images[i].rect);
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
