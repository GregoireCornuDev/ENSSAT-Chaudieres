#include "control_panel_gauge.h"

Gauge create_gauge(int x, int y, int width, int height, SDL_Color fg, SDL_Color bg) {
    Gauge gauge = {x, y, width, height, 0, fg, bg}; // Par défaut, valeur à 0
    return gauge;
}

void render_gauge(SDL_Renderer* renderer, Gauge* gauge) {
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

void update_gauge(Gauge* gauge, float new_value) {
    if (!gauge) return;

    // Limiter la valeur entre 0 et 100 pour rester dans les limites de la jauge
    if (new_value < 0) {
        gauge->value = 0;
    } else if (new_value > 100) {
        gauge->value = 100;
    } else {
        gauge->value = new_value;
    }
}

