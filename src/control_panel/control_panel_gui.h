#ifndef CONTROL_PANEL_GUI_H
#define CONTROL_PANEL_GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


// Structure principale du panneau de contrôle
typedef struct ControlPanelGUI {
    SDL_Renderer *renderer;    // Renderer pour dessiner
    SDL_Texture **textures;    // Tableau de textures
    int texture_count;         // Nombre de textures chargées
} ControlPanelGUI;

// Fonction pour initialiser le panneau de contrôle
ControlPanelGUI *control_panel_gui_init(SDL_Renderer *renderer);

// Fonction pour afficher les images
void control_panel_gui_render(ControlPanelGUI *panel);

// Fonction pour nettoyer les ressources
void control_panel_gui_destroy(ControlPanelGUI *panel);

#endif
