#ifndef CONTROL_PANEL_CONFIG_H
#define CONTROL_PANEL_CONFIG_H

#include <SDL2/SDL.h>

// Structure pour définir les paramètres d'une image
typedef struct {
    const char *file_path; // Chemin de l'image
    SDL_Rect rect;         // Position et taille (x, y, w, h)
} ImageConfig;

// Liste de configuration des images
extern const ImageConfig control_panel_images[];
extern const int control_panel_image_count;

#endif
