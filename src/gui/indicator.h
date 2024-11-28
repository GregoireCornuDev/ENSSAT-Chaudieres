#ifndef INDICATOR_H
#define INDICATOR_H

#include <SDL.h>

// Structure pour représenter un indicateur avec un label et une valeur
typedef struct {
    SDL_Rect rect;          // Rectangle pour l'indicateur
    SDL_Color color;        // Couleur de l'indicateur
    SDL_Color text_color;   // Couleur du texte
    char label[50];         // Texte du label
    float value;            // Valeur à afficher
    SDL_Texture *label_texture;  // Texture pour le texte
    SDL_Texture *value_texture;  // Texture pour la valeur
} Indicator;

// Fonction pour initialiser un indicateur
Indicator* indicator_init(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color, SDL_Color text_color, const char *label);

// Fonction pour mettre à jour la valeur de l'indicateur
void indicator_update(Indicator *indicator, SDL_Renderer *renderer, float value);

// Fonction pour dessiner l'indicateur
void indicator_render(SDL_Renderer *renderer, Indicator *indicator);

// Fonction pour détruire un indicateur
void indicator_destroy(Indicator *indicator);

#endif
