#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "central_manager.h"

#include <errno.h>

#include "control_panel_gui.h"
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
    CentralManager *central = (void*)arg;//central_manager_init();

    if(DEBUG == true) {
        // Boucle blanche
        int i;
        while(1) {
            i = 0;
            sleep(1);
        }
    }

    // Initialiser le buffer avec une taille dynamique
    CircularBuffer *water_buffer = circular_buffer_init(5);
    /*
     *if (circular_buffer_init(water_buffer, 5) != 0) {
        printf("Erreur lors de l'initialisation du buffer\n");
        return NULL;
    }
    */
    printf("Circulare Buffer OK \n");

    while (1) {

      //  pthread_mutex_lock(&water_level_mutex);
        read(central->water_level_pipe[0], &water_level, sizeof(water_level));
     //   pthread_mutex_unlock(&water_level_mutex);

        // Affichage du niveau d'eau enregistré
        printf("CentralManager water level : %f \n", water_level);

        //   pthread_mutex_unlock(&water_level_mutex);

        // Affichage du niveau d'eau enregistré
        printf("CentralManager water level : %f \n", water_level);

        // Ajout du nieavu d'eau dans le buffer
        circular_buffer_add(water_buffer, water_level);
        //add_value_to_buffer(&water_buffer, water_level, WATER_TIME_INTERVAL);
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


    }

    return NULL;
}

CentralManager *central_manager_init() {
    CentralManager *central = (CentralManager*)malloc(sizeof(CentralManager));
    return central;

}

