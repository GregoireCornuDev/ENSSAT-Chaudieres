#include "control_panel_config.h"

// Configuration des images du panneau de contrôle
const ImageConfig control_panel_images[] = {
    {"resources/image1.png", {50, 50, 200, 200}},  // Image 1 : position (50, 50), taille 200x200
    {"resources/image2.png", {300, 50, 200, 200}} // Image 2 : position (300, 50), taille 200x200
};

// Nombre total d'images
const int control_panel_image_count = sizeof(control_panel_images) / sizeof(ImageConfig);
