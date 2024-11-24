
#include "values_average.h"

void add_value_to_buffer(ValueBuffer *buffer, int new_value, int max_value) {
    // Ajouter la nouvelle valeur dans le buffer
    buffer->values[buffer->index] = new_value;

    // Mettre à jour l'indice (buffer circulaire)
    buffer->index = (buffer->index + 1) % max_value;

    // Si le buffer n'est pas encore plein, augmenter le compteur
    if (buffer->count < max_value) {
        buffer->count++;
    }
}

float calculate_average(ValueBuffer *buffer) {
    int sum = 0;

    // Calculer la somme des valeurs dans le buffer
    for (int i = 0; i < buffer->count; i++) {
        sum += buffer->values[i];
    }

    // Calculer la moyenne
    return (float)sum / buffer->count;
}

void add_values_and_calculate_average(ValueBuffer *buffer, float *values, int max_value, float *average) {
    // Ajouter chaque valeur dans le buffer
    for (int i = 0; i < max_value; i++) {
        add_value_to_buffer(buffer, values[i], max_value);
    }

    // Calculer la moyenne
    *average = calculate_average(buffer);
}

