#include "water_tank_manager.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Fonction principale du thread
void* water_tank_manager_thread(void* arg) {

    WaterTankManager* tank = (WaterTankManager*)arg;
    char supply_command = '0';  // Vanne d'approvisionnement fermée par défaut
    float use_command = 0.0;    // Vanne de sortie fermée par défaut (0.0 à 1.0)
    float water_level = 0;    // Niveau de l'eau

    int i;
    while(1)
    {
        // Rien
        i = 0;
    }


    // Initialisation du mutex
    //pthread_mutex_init(&tank->water_level_mutex, NULL);

    while (1) {

        printf("Water Tank Manager Thread started\n");

        //pthread_mutex_lock(&tank->water_level_mutex);

        if (read(tank->water_sensor_pipe[0], &water_level, sizeof(water_level)) > 0) {
            // Envoie au central_manager via son pipe
            write(tank->water_level_pipe[1], &water_level, sizeof(water_level));
        }

        // Afficher la valeur contenue dans le pipe water_level_pipe à la fin de la fonction
        float pipe_value = 0;
        if (read(tank->water_level_pipe[0], &pipe_value, sizeof(pipe_value)) > 0) {
            printf("WaterTankManager : Valeur lue depuis water_level_pipe : %f\n", pipe_value);
        } else {
            printf("Erreur de lecture du pipe water_level_pipe\n");
        }

       // pthread_mutex_unlock(&tank->water_level_mutex);

        // Pause de 1 seconde
        sleep(1);
    }
}
