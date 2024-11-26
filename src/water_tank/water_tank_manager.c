#include "water_tank_manager.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../config.h"
#include "../mutex_manager.h"


// Fonction principale du thread
void* water_tank_manager_thread(void* arg) {

    printf("Water Tank Manager Thread started \n");

    WaterTankManager *tank = (void*)arg;//water_tank_manager_init();
    if (!tank) {
        printf("Échec d'initialisation de WaterTankManager\n");
        return NULL;
    }

    char supply_command = '0';  // Vanne d'approvisionnement fermée par défaut
    float use_command = 0.0;    // Vanne de sortie fermée par défaut (0.0 à 1.0)
    float water_level = 0.0;    // Niveau de l'eau

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
        //sleep(1);

        //pthread_mutex_lock(&water_level_sensor_mutex);
        // Lecture du niveau d'eau envoyé par le simulateur
        if (read(tank->water_level_sensor_pipe[0], &water_level, sizeof(water_level)) == -1) {
            perror("Erreur de lecture dans tank->water_level_sensor_pipe \n");
        }
        //pthread_mutex_unlock(&water_level_sensor_mutex);

        //pthread_mutex_lock(&water_level_mutex);
        // Ecriture du niveau d'eau à envoyer par le tank manager
        if (write(tank->water_level_pipe[1], &water_level, sizeof(water_level)) == -1) {
            perror("Erreur d'écriture dans tank->water_level_pipe \n");
        }
        //pthread_mutex_unlock(&water_level_mutex);

        // Affichage du niveau d'eau enregistré
        printf("TankManager water level : %f \n", water_level);



    }
}

WaterTankManager *water_tank_manager_init() {
    WaterTankManager* tank = (WaterTankManager*)malloc(sizeof(WaterTankManager));
    if (!tank) { // Vérifie si l'allocation a échoué
        perror("Erreur d'allocation mémoire pour WaterTankManager");
        return NULL;
    }
    return tank;

}
