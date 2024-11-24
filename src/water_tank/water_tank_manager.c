#include "water_tank_manager.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

// Fonction principale du thread
void* water_tank_manager_thread(void* arg) {

    WaterTankManager* tank = (WaterTankManager*)arg;
    char supply_command = '0';  // Vanne d'approvisionnement fermée par défaut
    float use_command = 0.0;    // Vanne de sortie fermée par défaut (0.0 à 1.0)
    int water_level = 0;    // Niveau de l'eau

    // Initialisation du mutex
    pthread_mutex_init(&tank->water_level_mutex, NULL);

    while (1) {

        sleep(30);

        if (pipe(tank->water_sensor_pipe) == -1) {
            perror("Erreur lors de la création du pipe");
            exit(EXIT_FAILURE);
        }
        if (pipe(tank->water_level_pipe) == -1) {
            perror("Erreur lors de la création du pipe");
            exit(EXIT_FAILURE);
        }

        if (tank->water_level_pipe[0] == -1 || tank->water_level_pipe[1] == -1) {
            perror("Erreur dans les descripteurs de pipe water_level_pipe");
            exit(EXIT_FAILURE);
        }



        if (pthread_mutex_lock(&tank->water_level_mutex) == 0)
        {
            printf("water_level_pipe[1]: %d\n", tank->water_level_pipe[1]);
            if (tank->water_level_pipe[1] == -1) {
                perror("Invalid write descriptor for water_level_pipe");
                exit(EXIT_FAILURE);
            } else {
                printf("water_level_pipe[1] OK : %d\n", tank->water_level_pipe[1]);
            }

            pthread_mutex_unlock(&tank->water_level_mutex);
        } else {
            perror("Failed to lock mutex");
        }

        if (read(tank->water_sensor_pipe[0], &water_level, sizeof(water_level)) > 0) {
            printf("Water level received from simulator: %d\n", water_level);
            // Envoie au central_manager via son pipe
            printf("water_level_pipe[1]: %d\n", tank->water_level_pipe[1]);
            printf("water_level: %d\n", water_level);
            write(tank->water_level_pipe[1], &water_level, sizeof(water_level));
        }

        printf("dodo !");
        // Pause de 1 seconde
        sleep(1);
    }
}
