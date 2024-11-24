#ifndef CONTROL_PANEL_GUI_H
#define CONTROL_PANEL_GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "control_panel_gauge.h" // Inclusion pour la jauge

// Structure représentant une image à afficher
typedef struct {
    const char *file_path; // Chemin vers l'image
    SDL_Rect rect;         // Position et dimensions de l'image
} ControlPanelImage;

// Structure principale du panneau de contrôle
typedef struct {
    SDL_Renderer *renderer;    // Renderer SDL
    SDL_Texture **textures;    // Tableau des textures
    int texture_count;         // Nombre de textures
    Gauge gauge;               // Jauge verticale
} ControlPanelGUI;

typedef struct
{
    float water_average;
} ControlPanelData;

// Fonction pour initialiser le panneau de contrôle
ControlPanelGUI *control_panel_gui_init(SDL_Renderer *renderer);

// Fonction pour afficher les images
void control_panel_gui_render(ControlPanelGUI *panel);

// Met à jour l'interface graphique
void control_panel_gui_update(ControlPanelGUI *panel, const ControlPanelData *data);

// Fonction pour nettoyer les ressources
void control_panel_gui_destroy(ControlPanelGUI *panel);

#endif
