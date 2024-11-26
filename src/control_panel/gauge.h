#ifndef CONTROL_PANEL_GAUGE_H
#define CONTROL_PANEL_GAUGE_H

#include <SDL2/SDL.h>

// Structure pour configurer la jauge
typedef struct {
    int x, y;        // Position de la jauge dans la fenêtre
    int width;       // Largeur de la jauge
    int height;      // Hauteur de la jauge
    float value;     // Valeur de remplissage
    SDL_Color fg;    // Couleur de la jauge (avant-plan)
    SDL_Color bg;    // Couleur de fond
} Gauge;

// Initialise une jauge
Gauge *gauge_init(int x, int y, int width, int height, SDL_Color fg, SDL_Color bg);

// Dessine la jauge dans le renderer SDL
void gauge_render(SDL_Renderer* renderer, Gauge* gauge);

// Met à jour la jauge
void gauge_update(Gauge* gauge, float new_value);

// Fonction pour détruire un jauge
void gauge_destroy(Gauge *gauge);

#endif // CONTROL_PANEL_GAUGE_H
