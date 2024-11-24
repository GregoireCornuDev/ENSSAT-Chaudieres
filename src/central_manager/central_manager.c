#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "central_manager.h"

#include <unistd.h>

#include "control_panel_gui.h"
#include "control_panel_config.h"
#include "values_average.h"


// Thread de gestion du panneau de contrôle
void *central_manager_thread(void *arg) {

    CentralManagerData* data = {0};
    ValueBuffer water_buffer = {{0}, 0, 0};  // Buffer pour les niveaux d'eau
    ValueBuffer fuel_buffer = {{0}, 0, 0};   // Buffer pour les niveaux de carburant


    float water_level = 0.0;
    float water_average = 0.0;
    float fuel_level = 0.0;
    float fuel_average = 0.0;



    while (1) {

        water_level = data->water_level;
        water_average = data->water_average;
        fuel_level = data->fuel_level;
        fuel_average = data->fuel_average;

        // Lit le niveau d'eau dans le pipe
        if (read(data->water_level_pipe[0], &data->water_level, sizeof(&data->water_level)) > 0) {
            printf("Water level received from simulator: %f\n", data->water_level);

            // Calculer la moyenne des niveaux d'eau
            if (water_buffer.count == WATER_TIME_INTERVAL) {
                add_values_and_calculate_average(&water_buffer, &data->water_level, WATER_TIME_INTERVAL, &data->water_average);
                printf("Water average over the last %d values: %.2f\n", WATER_TIME_INTERVAL, data->water_average);
            }

            // Envoie au central_manager via son pipe
            write(data->water_average_pipe[1], &data->water_average, sizeof(data->water_average));
            printf("Water level send to control panel: %f", data->water_average);
        }

/*
        // Lit le niveau de fuel dans le pipe
        if (read(data->fuel_level_pipe[0], &data->fuel_level, sizeof(&data->fuel_level)) > 0) {
            printf("Fuel level received from simulator: %f\n", data->fuel_level);
            if (fuel_buffer.count == FUEL_TIME_INTERVAL) {
                add_values_and_calculate_average(&fuel_buffer, &data->fuel_level, FUEL_TIME_INTERVAL, &data->fuel_average);
                printf("Fuel average over the last %d values: %.2f\n", FUEL_TIME_INTERVAL, data->fuel_average);
            }

            // Envoie au central_manager via son pipe
            write(data->fuel_average_pipe[1], &data->fuel_average, sizeof(data->fuel_average));
            printf("Fuel level send to control panel: %f", data->fuel_average);

*/
        // Attendre avant la prochaine mise à jour (ex: 1 seconde)
        sleep(1);
    }

    return NULL;
}