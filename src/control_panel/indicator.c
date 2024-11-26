#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "indicator.h"
#include <control_panel_config.h>
#include <unistd.h>
#include <limits.h>

#include "../config.h"

// Fonction pour créer une texture de texte
static SDL_Texture* create_text_texture(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) {
        printf("Erreur de création de surface de texte : %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Initialiser un indicateur
Indicator* indicator_init(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color, SDL_Color text_color, const char *label) {
    if (!renderer || !label) return NULL;

    Indicator *indicator = malloc(sizeof(Indicator));
    if (!indicator) return NULL;

    indicator->rect = (SDL_Rect){x, y, w, h};
    indicator->color = color;
    indicator->text_color = text_color;
    indicator->value = 0.0f;

    snprintf(indicator->label, sizeof(indicator->label), "%s", label);


    // Initialisation de TTF
    if (TTF_Init() == -1) {
        printf("Erreur SDL_ttf init : %s\n", TTF_GetError());
        return NULL;
    }

    // Initialiser les polices
    TTF_Font *font = TTF_OpenFont("resources/Impacted2.0.ttf", 16);
    if (!font) {
        printf("Erreur de chargement de police 1: %s\n", TTF_GetError());
        free(indicator);
        return NULL;
    }

    indicator->label_texture = create_text_texture(renderer, font, label, text_color);
    indicator->value_texture = NULL; // Sera mis à jour plus tard avec la valeur
    TTF_CloseFont(font);

    return indicator;
}

// Mettre à jour la valeur de l'indicateur
void indicator_update(Indicator *indicator, SDL_Renderer *renderer, float new_value) {
    if (!indicator || !renderer) {
        perror("Erreur de chargement de indicator ou du renderer");
        return;
    }
    printf("Indicator value: %f\n", new_value);
    indicator->value = new_value;

    // Mettre à jour la texture de la valeur
    TTF_Font *font = TTF_OpenFont("resources/Impacted2.0.ttf", 16);
    if (!font) {
        printf("Erreur de chargement de police 2: %s\n", TTF_GetError());
        return;
    }

    char value_text[20];
    snprintf(value_text, sizeof(value_text), "%.2f", new_value);

    if (indicator->value_texture) {
        SDL_DestroyTexture(indicator->value_texture);
    }
    indicator->value_texture = create_text_texture(renderer, font, value_text, indicator->text_color);
    TTF_CloseFont(font);
}

// Dessiner l'indicateur
void indicator_render(SDL_Renderer *renderer, Indicator *indicator) {
    if (!renderer || !indicator) return;

    // Dessiner le rectangle
    SDL_SetRenderDrawColor(renderer, indicator->color.r, indicator->color.g, indicator->color.b, indicator->color.a);
    SDL_RenderFillRect(renderer, &indicator->rect);

    // Dessiner le label
    if (indicator->label_texture) {
        SDL_Rect label_dest = {indicator->rect.x + 5, indicator->rect.y + 5, 0, 0};
        SDL_QueryTexture(indicator->label_texture, NULL, NULL, &label_dest.w, &label_dest.h);
        SDL_RenderCopy(renderer, indicator->label_texture, NULL, &label_dest);
    }

    // Dessiner la valeur
    if (indicator->value_texture) {
        SDL_Rect value_dest = {indicator->rect.x + 5, indicator->rect.y + 30, 0, 0};
        SDL_QueryTexture(indicator->value_texture, NULL, NULL, &value_dest.w, &value_dest.h);
        SDL_RenderCopy(renderer, indicator->value_texture, NULL, &value_dest);
    }
}

// Détruire un indicateur
void indicator_destroy(Indicator *indicator) {
    if (!indicator) return;

    if (indicator->label_texture) SDL_DestroyTexture(indicator->label_texture);
    if (indicator->value_texture) SDL_DestroyTexture(indicator->value_texture);
    free(indicator);
}
