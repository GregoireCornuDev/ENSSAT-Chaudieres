#include "water_tank_simulation.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../config.h"
#include "../mutex_manager.h"

void *water_tank_simulation_thread(void* arg) {

    printf("Water Tank Simulation thread started \n");

    WaterTankSimulation *simulator = (void*)arg;//water_tank_simulation_init();

    char supply_command, drain_command;

    // Initialisation du réservoir
    init_water_tank(simulator);

    float water_level = 0.0;

    if(DEBUG == true) {
        // Boucle blanche
        int i;
        while(1) {
            i = 0;
            sleep(1);
        }
    }


    while (1) {

        // Pause de 1 seconde
        sleep(1);

        if (water_level <= 100) {
            water_level += 1;
        }

        /*
        // Lecture des commandes pour la vanne d'approvisionnement
        if (read(tank->supply_pipe[0], &supply_command, 1) > 0) {
            if (supply_command == '1') {
                printf("Supply valve opened.\n");
            } else if (supply_command == '0') {
                printf("Supply valve closed.\n");
            }
        }

        // Lecture des commandes pour la vanne de sortie
        if (read(tank->drain_pipe[0], &drain_command, 1) > 0) {
            if (drain_command == '1') {
                printf("Drain valve opened.\n");
            } else if (drain_command == '0') {
                printf("Drain valve closed.\n");
            }
        }

        // Mise à jour du niveau d'eau
        if (supply_command == '1') {
            tank->water_level += 1;
        }
        if (drain_command == '1') {
            tank->water_level -= 2;
        }
        */

        // Affichage du niveau d'eau enregistré
        printf("Simulation water level: %f \n", water_level);

        //pthread_mutex_lock(&water_level_sensor_mutex);
        // Envoyer la nouvelle valeur de water_level à travers le pipe
        if (write(simulator->water_level_sensor_pipe[1], &water_level, sizeof(water_level)) == -1) {
            perror("Erreur d'écriture dans simulator->water_level_sensor_pipe \n");
        }
        //pthread_mutex_unlock(&water_level_sensor_mutex);



    }

    return NULL;
}

WaterTankSimulation *water_tank_simulation_init() {
    WaterTankSimulation *simulation = (WaterTankSimulation*)malloc(sizeof(WaterTankSimulation));
    return simulation;
}

void init_water_tank(WaterTankSimulation* tank) {
    tank->water_level = 40;
}
