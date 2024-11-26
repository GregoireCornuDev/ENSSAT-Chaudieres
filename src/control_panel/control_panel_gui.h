#ifndef CONTROL_PANEL_GUI_H
#define CONTROL_PANEL_GUI_H

#include <control_panel_manager.h>
#include <SDL2/SDL.h>
#include "gauge.h"
#include "indicator.h"

// Structure représentant une image à afficher
typedef struct {
    const char *file_path; // Chemin vers l'image
    SDL_Rect rect;         // Position et dimensions de l'image
} ControlPanelImage;

// Structure principale du panneau de contrôle
typedef struct {
    SDL_Window *window;        // Fenêtre SDL
    SDL_Renderer *renderer;    // Renderer SDL
    SDL_Texture **textures;    // Tableau des textures
    int texture_count;         // Nombre de textures
    Gauge *gauge;               // Jauge verticale
    Indicator *water_indicator; // Indicateur de l'eau
    int water_average_gui_pipe[2]; // Pipe pour recevoir le niveau moyen depuis le ControlPanelManager
} ControlPanelGUI;

// Fonction principale du thread
void *control_panel_gui_thread(void *arg);

// Fonction pour initialiser le panneau de contrôle
//ControlPanelGUI *control_panel_gui_init();
void *control_panel_gui_init(ControlPanelGUI *gui);

// Fonction pour afficher les images
void control_panel_gui_render(ControlPanelGUI *gui);

// Met à jour l'interface graphique
void control_panel_gui_update(ControlPanelGUI *gui);

// Fonction pour nettoyer les ressources
void control_panel_gui_destroy(ControlPanelGUI *gui);

#endif
