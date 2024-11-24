#include "fuel_tank_manager.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


// Fonction principale du thread
void* fuel_tank_manager_thread(void* arg) {
    FuelTankManager* reservoir = (FuelTankManager*)arg;
    char supply_command = '0';  // Vanne d'approvisionnement fermée par défaut
    float use_command = 0.0;    // Vanne de sortie fermée par défaut (0.0 à 1.0)

    while (1) {
        // Lecture des commandes pour la vanne d'approvisionnement
        if (read(reservoir->supply_pipe[0], &supply_command, 1) > 0) {
            if (supply_command == '1') {
                printf("Supply valve opened.\n");
            } else if (supply_command == '0') {
                printf("Supply valve closed.\n");
            }
        }

        // Lecture des commandes pour la vanne de sortie (proportionnelle)
        if (read(reservoir->use_pipe[0], &use_command, sizeof(use_command)) > 0) {
            if (use_command >= 0.0 && use_command <= 1.0) {
                printf("Use valve set to %.2f\n", use_command);
            }
        }

        // Mise à jour du niveau d'eau en fonction des commandes des vannes
        if (supply_command == '1') {
            reservoir->fuel_level += 1;  // Vanne d'approvisionnement
        }

        // La vanne de sortie proportionnelle (0.0 à 1.0)
        reservoir->fuel_level -= 2 * use_command;  // Vanne de sortie

        // Vérifier que le niveau d'eau reste dans des limites réalistes
        if (reservoir->fuel_level < 0) {
            reservoir->fuel_level = 0;  // Le réservoir ne peut pas être vide
        }

        // Affichage du niveau d'eau
        //printf("Current fuel level: %d\n", reservoir->fuel_level);

        // Pause de 1 seconde
        sleep(1);
    }

    return NULL;
}
