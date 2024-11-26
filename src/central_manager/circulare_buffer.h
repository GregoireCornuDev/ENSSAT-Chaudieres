//
// Created by gregoire on 24/11/24.
//

#ifndef VALUES_AVERAGE_H
#define VALUES_AVERAGE_H


typedef struct {
    float *buffer; // Tableau dynamique pour stocker les données
    int head;      // Indice du prochain emplacement d'écriture
    int count;     // Nombre d'éléments actuellement dans le buffer
    int size;      // Taille maximale du buffer
} CircularBuffer;

// Initialiser le buffer circulaire avec une taille donnée
int _circular_buffer_init(CircularBuffer *cb, int buffer_size);
CircularBuffer *circular_buffer_init(int buffer_size);

// Ajouter une valeur dans le buffer circulaire
void circular_buffer_add(CircularBuffer *cb, float value);

// Afficher les valeurs du buffer circulaire pour vérification
void circular_buffer_print(CircularBuffer *cb);

// Réaliser une moyenne des valeurs du buffer
float average_buffer(CircularBuffer *cb);

// Libérer la mémoire allouée pour le buffer circulaire
void circular_buffer_free(CircularBuffer *cb);


#endif //VALUES_AVERAGE_H
