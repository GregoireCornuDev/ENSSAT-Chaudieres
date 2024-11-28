#include "../control_panel/gauge.h"

Gauge *gauge_init(int x, int y, int width, int height, SDL_Color fg, SDL_Color bg) {

    Gauge *gauge = (Gauge *)malloc(sizeof(Gauge));
    gauge->x = x;
    gauge->y = y;
    gauge->width = width;
    gauge->height = height;
    gauge->fg = fg;
    gauge->bg = bg;

    return gauge;
}

void gauge_render(SDL_Renderer* renderer, Gauge* gauge) {
    // Dessiner le fond de la jauge (rectangle complet)
    SDL_Rect bg_rect = {gauge->x, gauge->y, gauge->width, gauge->height};
    SDL_SetRenderDrawColor(renderer, gauge->bg.r, gauge->bg.g, gauge->bg.b, gauge->bg.a);
    SDL_RenderFillRect(renderer, &bg_rect);

    // Calculer la hauteur du rectangle rempli en fonction de la valeur
    int filled_height = (gauge->value * gauge->height) / 100;

    // Dessiner la partie remplie (rectangle proportionnel)
    SDL_Rect fg_rect = {gauge->x, gauge->y + gauge->height - filled_height, gauge->width, filled_height};
    SDL_SetRenderDrawColor(renderer, gauge->fg.r, gauge->fg.g, gauge->fg.b, gauge->fg.a);
    SDL_RenderFillRect(renderer, &fg_rect);
}


void gauge_update(Gauge* gauge, float new_value) {
    if (!gauge) return;

    //printff("Gauge value: %f\n", new_value);
    // Limiter la valeur entre 0 et 100 pour rester dans les limites de la jauge
    if (new_value < 0) {
        gauge->value = 0;
    } else if (new_value > 100) {
        gauge->value = 100;
    } else {
        gauge->value = new_value;
    }
}

// Détruire une jauge
void gauge_destroy(Gauge *gauge)
{
    if (!gauge) return;

    free(gauge);
}

