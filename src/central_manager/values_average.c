#define MAX_VALUES 5  // Le nombre de secondes à prendre en compte

typedef struct {
    int values[MAX_VALUES];  // Tableau pour stocker les niveaux
    int count;                     // Compteur pour suivre le nombre de valeurs
    int index;                     // Indice où la prochaine valeur sera stockée
} WaterLevelBuffer;

#include <stdio.h>


void add_value(WaterLevelBuffer *buffer, int new_value) {

    // Ajouter la nouvelle valeur dans le buffer
    buffer->water_levels[buffer->index] = new_value;

    // Mettre à jour l'indice (c'est un buffer circulaire)
    buffer->index = (buffer->index + 1) % MAX_VALUES;

    // Si le buffer n'est pas encore plein, augmenter le compteur
    if (buffer->count < MAX_VALUES) {
        buffer->count++;
    }
}

void calculate_average(WaterLevelBuffer *buffer, int new_value) {

    // Calcul de la moyenne des valeurs
    int sum = 0;
    for (int i = 0; i < buffer->count; i++) {
        sum += buffer->water_levels[i];
    }

    // Calcul de la moyenne
    float average = (float)sum / buffer->count;

    // Afficher la moyenne
    printf("Average water level over the last %d seconds: %.2f\n", buffer->count, average);
}

void get_5seconds_average(WaterLevelBuffer *buffer) {}