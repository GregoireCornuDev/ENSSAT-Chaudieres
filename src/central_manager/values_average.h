//
// Created by gregoire on 24/11/24.
//

#ifndef VALUES_AVERAGE_H
#define VALUES_AVERAGE_H

typedef struct {
    float values[10];  // Tableau pour stocker les valeurs (niveau d'eau ou de carburant)
    int count;         // Nombre de valeurs actuellement dans le buffer
    int index;         // Indice du prochain emplacement à écrire dans le buffer
} ValueBuffer;

void create_buffer(ValueBuffer *buffer, int buffer_size);

void add_value_to_buffer(ValueBuffer *buffer, float new_value, int max_value);

float calculate_average(ValueBuffer *buffer);

void add_values_and_calculate_average(ValueBuffer *buffer, float *values, int num_values, float *average);


#endif //VALUES_AVERAGE_H
