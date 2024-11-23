#include "water_tank_simulation.h"
#include <stdio.h>
#include <unistd.h>

void* water_tank_simulation(void* arg) {
    WaterTank* tank = (WaterTank*)arg;
    char supply_command, drain_command;

    while (1) {
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

        // Affichage du niveau d'eau
        printf("Current water level: %d\n", tank->water_level);

        // Pause de 1 seconde
        sleep(1);
    }

    return NULL;
}
