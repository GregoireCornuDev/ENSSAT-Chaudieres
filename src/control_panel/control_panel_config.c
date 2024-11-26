#include "control_panel_config.h"

// Configuration des images du panneau de contrôle
const ImageConfig control_panel_images[] = {
    {"resources/image1.png", {50, 50, 200, 200}},  // Image 1 : position (50, 50), taille 200x200
    {"resources/image2.png", {300, 50, 200, 200}} // Image 2 : position (300, 50), taille 200x200
};

const FontConfig font_config = {
    {"resources/Impacted2.O.ttf"}
};

// Configuration de la jauge (position et taille)
const GaugeConfig control_panel_gauge_config = {
    50, 50,    // Position de la jauge (X, Y)
    30, 200,   // Taille de la jauge (largeur, hauteur)
    {0, 255, 0, 255}, // Couleur avant (vert)
    {50, 50, 50, 255}  // Couleur arrière (gris)
};

// Nombre total d'images
const int control_panel_image_count = sizeof(control_panel_images) / sizeof(ImageConfig);
