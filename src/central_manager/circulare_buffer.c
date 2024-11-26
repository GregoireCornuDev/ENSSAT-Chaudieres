
#include "circulare_buffer.h"

#include <stdio.h>
#include <stdlib.h>

// Initialiser le buffer circulaire avec une taille donnée
int _circular_buffer_init(CircularBuffer *cb,int buffer_size) {

    if (buffer_size <= 0) return -1; // Vérifier que la taille est valide

    cb->buffer = (float *)malloc(buffer_size * sizeof(float));
    if (!cb->buffer) return -1; // Vérifier que l'allocation a réussi

    cb->head = 0;
    cb->count = 0;
    cb->size = buffer_size;

    return 0; // Succès
}

CircularBuffer *circular_buffer_init(int buffer_size) {

    CircularBuffer *cb = malloc(sizeof(CircularBuffer));

    if (buffer_size <= 0) return NULL; // Vérifier que la taille est valide

    cb->buffer = (float *)malloc(buffer_size * sizeof(float));
    if (!cb->buffer) return NULL; // Vérifier que l'allocation a réussi

    cb->head = 0;
    cb->count = 0;
    cb->size = buffer_size;

    return cb; // Succès
}

// Ajouter une valeur dans le buffer circulaire
void circular_buffer_add(CircularBuffer *cb, float value) {
    if (!cb->buffer) return; // S'assurer que le buffer est valide

    // Ajouter la valeur à l'emplacement courant
    cb->buffer[cb->head] = value;

    // Incrémenter l'indice circulaire
    cb->head = (cb->head + 1) % cb->size;

    // Mettre à jour le nombre d'éléments dans le buffer
    if (cb->count < cb->size) {
        cb->count++; // Si le buffer n'est pas plein, augmenter le compteur
    }
}

// Afficher les valeurs du buffer circulaire pour vérification
void circular_buffer_print(CircularBuffer *cb) {
    if (!cb->buffer) return; // S'assurer que le buffer est valide

    printf("Circular Buffer: ");
    for (int i = 0; i < cb->count; i++) {
        int index = (cb->head + cb->size - cb->count + i) % cb->size; // Calculer l'indice réel
        printf("%f ", cb->buffer[index]);
    }
    printf("\n");
}

// Réaliser une moyenne des valeurs du buffer
float average_buffer(CircularBuffer *cb) {
    if (cb->count == 0) {
        printf("Le buffer est vide, impossible de calculer une moyenne.\n");
        return 0.0f; // Retourne 0 si le buffer est vide
    }

    // Initialisation de somme
    float sum = 0.0f;

    // Parcourir toutes les valeurs présentes dans le buffer
    for (int i = 0; i < cb->count; i++) {
        int index = (cb->head + cb->size - cb->count + i) % cb->size;
        sum += cb->buffer[index];
    }

    // Calculer la moyenne
    return sum / cb->count;
}


// Libérer la mémoire allouée pour le buffer circulaire
void circular_buffer_free(CircularBuffer *cb) {
    free(cb->buffer); // Libérer la mémoire du tableau
    cb->buffer = NULL; // Réinitialiser le pointeur pour éviter des problèmes
    cb->head = 0;
    cb->count = 0;
    cb->size = 0;
}


