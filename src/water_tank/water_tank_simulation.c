#include "water_tank_simulation.h"
#include <stdio.h>
#include <unistd.h>

void* water_tank_simulation_thread(void* arg) {
    WaterTankSimulator* tank = (WaterTankSimulator*)arg;
    char supply_command, drain_command;

    init_water_tank(tank);



    float water_level = 40.0;


    int i;
    while(1)
    {
        // Rien
        i = 0;
    }


    while (1) {
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
        if (water_level <= 100) {
            //water_level += 1;
        }

        printf("water level: %f\n", water_level);

        // Affichage du niveau d'eau
        printf("Current water level: %d\n", tank->water_level);

        // Envoyer la nouvelle valeur de water_level à travers le pipe
        if (write(tank->water_sensor_pipe[1], &tank->water_level, sizeof(tank->water_level)) == -1) {
            perror("Error writing to water_level_pipe");
        }

        // Pause de 1 seconde
        sleep(1);
    }

    return NULL;
}

void init_water_tank(WaterTankSimulator* tank) {
    tank->water_level = 40;
}
