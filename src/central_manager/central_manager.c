#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "central_manager.h"

#include <errno.h>

#include "../control_panel/gui.h"
#include "control_panel_config.h"
#include "circulare_buffer.h"
#include "../config.h"
#include "../mutex_manager.h"


// Thread de gestion du panneau de contrôle
void *central_manager_thread(void *arg) {

    printf("Central Manager thread started \n");

    float water_level = 0.0;
    float water_average = 0.0;
    float fuel_level = 0.0;
    float fuel_average = 0.0;

    // Initialise le central manager
    CentralManager *central = (void*)arg;

    if(MODE_DEBUG == true) {
        // Boucle blanche
        int i;
        while(1) {
            i = 0;
            sleep(1);
        }
    }

    // Initialiser le buffer avec une taille dynamique
    CircularBuffer *water_buffer = circular_buffer_init(5);
    CircularBuffer *fuel_buffer = circular_buffer_init(10);


    printf("Circulare Buffer OK \n");

    while (1) {

      //  pthread_mutex_lock(&water_level_mutex);
        read(central->water_level_pipe[0], &water_level, sizeof(water_level));
     //   pthread_mutex_unlock(&water_level_mutex);

        // Affichage du niveau d'eau enregistré
        printf("CentralManager water level : %f \n", water_level);

        // Ajout du nieavu d'eau dans le buffer
        circular_buffer_add(water_buffer, water_level);

        // Calcul de la moyenne de niveau d'eau
        water_average = average_buffer(water_buffer);

        // Affichage du niveau d'eau moyen calculé
        printf("CentralManager water average : %f \n", water_average);

        //pthread_mutex_lock(&water_average_mutex);
        // Ecriture du niveau d'eau à envoyer par le central manager
        if (write(central->water_average_pipe[1], &water_average, sizeof(water_average)) == -1) {
            perror("Erreur d'écriture dans central->water_average_pipe \n");
        }
        //pthread_mutex_unlock(&water_average_mutex);

        /** FUEL */

        //  pthread_mutex_lock(&water_level_mutex);
        read(central->fuel_level_pipe[0], &fuel_level, sizeof(fuel_level));
        //   pthread_mutex_unlock(&water_level_mutex);

        // Affichage du niveau d'eau enregistré
        printf("CentralManager fuel level : %f \n", fuel_level);

        // Ajout du niveau de fuel dans le buffer
        circular_buffer_add(fuel_buffer, fuel_level);

        // Calcul de la moyenne de niveau d'eau
        fuel_average = average_buffer(fuel_buffer);

        // Affichage du niveau d'eau moyen calculé
        printf("CentralManager fuel average : %f \n", fuel_average);

        //pthread_mutex_lock(&fuel_average);
        // Ecriture du niveau d'eau à envoyer par le central manager
        if (write(central->fuel_average_pipe[1], &fuel_average, sizeof(fuel_average)) == -1) {
            perror("Erreur d'écriture dans central->water_average_pipe \n");
        }
        //pthread_mutex_unlock(&fuel_average_mutex);


    }

    return NULL;
}

CentralManager *central_manager_init() {
    CentralManager *central = (CentralManager*)malloc(sizeof(CentralManager));
    return central;

}

