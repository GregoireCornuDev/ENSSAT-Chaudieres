#ifndef CONTROL_PANEL_CONFIG_H
#define CONTROL_PANEL_CONFIG_H

#include <SDL2/SDL.h>

// Structure pour définir les paramètres d'une image
typedef struct {
    const char *file_path; // Chemin de l'image
    SDL_Rect rect;         // Position et taille (x, y, w, h)
} ImageConfig;

// Structure représentant la configuration de la jauge
typedef struct {
    int x, y;               // Position de la jauge (coin supérieur gauche)
    int width, height;      // Dimensions de la jauge
    SDL_Color foreground;   // Couleur de la jauge (valeur)
    SDL_Color background;   // Couleur de l'arrière-plan de la jauge
} GaugeConfig;

// Déclaration de la configuration des images
extern const ImageConfig control_panel_images[];
extern const int control_panel_image_count;

// Déclaration de la configuration de la jauge
extern const GaugeConfig control_panel_gauge_config;

#endif
