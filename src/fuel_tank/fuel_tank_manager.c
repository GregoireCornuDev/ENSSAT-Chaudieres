#include "fuel_tank_manager.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../config.h"
#include "../mutex_manager.h"
#include <fcntl.h>    // Pour fcntl() et les constantes comme F_SETFL, O_NONBLOCK

// Fonction principale du thread
void* fuel_tank_manager_thread(void* arg) {

    printf("Fuel Tank Manager Thread started \n");

    FuelTankManager *tank = (void*)arg;
    if (!tank) {
        printf("Échec d'initialisation de FuelTankManager\n");
        return NULL;
    }

    float fuel_level = 0.0;    // Niveau de l'eau

    if(MODE_DEBUG == true) {
        // Boucle blanche
        int i;
        while(1) {
            i = 0;
            sleep(1);
        }
    }

    while (1) {

        // Receptionne le niveau de fuel depuis le réservoir (simulation)
        fuel_level_receives(tank);

        fuel_level = tank->fuel_level;

        // Affichage du niveau de fuel enregistré
        printf("TankManager fuel level : %f \n", fuel_level);

        // Transmet le niveau de fuel au Central Manager
        //fuel_level_send(tank);

        // Analyse les déclencheurs des capteurs et réagit en conséquence (commande les vannes)
        fuel_level_triggers_react(tank);
    }
}

// Initialise le Fuel Tank Manager
void fuel_tank_manager_init(FuelTankManager *fuel_manager) {

}

// S'informe sur le niveau de fuel
void fuel_level_receives(FuelTankManager *fuel_manager) {

    float fuel_level = fuel_manager->fuel_level;

    //pthread_mutex_lock(&fuel_level_sensor_mutex);
    // Lecture du niveau de fuel envoyé par le simulateur
    if (read(fuel_manager->fuel_level_sensor_pipe[0], &fuel_level, sizeof(fuel_level)) == -1) {

        perror("Erreur de lecture dans tank->fuel_level_sensor_pipe \n");
    }
    //pthread_mutex_unlock(&fuel_level_sensor_mutex);

    // Enregistre l'information dans la structure
    fuel_manager->fuel_level = fuel_level;
}

// Transmet le niveau de fuel
void fuel_level_send(FuelTankManager *fuel_manager) {

    float fuel_level = fuel_manager->fuel_level;

    //pthread_mutex_lock(&fuel_level_mutex);
    // Ecriture du niveau de fuel à envoyer par le tank manager
    if (write(fuel_manager->fuel_level_pipe[1], &fuel_level, sizeof(fuel_level)) == -1) {
        if (errno == EAGAIN) {
            // Pas de données, on passe à autre chose
            printf("Pas de données disponibles dans le pipe fuel_level_pipe.\n");
        } else {
            perror("Erreur d'écriture dans tank->fuel_level_pipe \n");
        }

    }
    //pthread_mutex_unlock(&fuel_level_mutex);
}

// Analyse les déclencheurs des capteurs
void fuel_level_triggers_react(FuelTankManager *fuel_manager) {

    char sensors_trigger = '0';

    // Rend le pipe non bloquant
    int flags = fcntl(fuel_manager->fuel_level_trigger_pipe[0], F_GETFL, 0);
    fcntl(fuel_manager->fuel_level_trigger_pipe[0], F_SETFL, flags | O_NONBLOCK);

    // Reçoit le déclenchement des capteurs
    if(read(fuel_manager->fuel_level_trigger_pipe[0], &sensors_trigger, sizeof(sensors_trigger)) > 0) {
        printf("Trigger : %c \n", sensors_trigger);

        if(sensors_trigger == 'H') {
            // Commande l'ouverture de la vanne d'approvisionnement
            fuel_supply_command(fuel_manager, 0);
            printf("Fermeture de la vanne d'approvisionnement en eau \n");
        } else if (sensors_trigger == 'B') {
            // Commande la fermeture de la vanne d'approvisionnement
            fuel_supply_command(fuel_manager, 1);
            printf("Ouverture de la vanne d'approvisionnement en eau \n");
        } else if (sensors_trigger == 'b') {
            // Commande la fermeture de la vanne d'approvisionnement
            fuel_supply_command(fuel_manager, 1);
            // Déclenche une alerte critique
            printf("Ouverture de la vanne d'approvisionnement en eau et alerte \n");
        } else {
            perror("Message sensors trigger non reconnu \n");
        }

    // Pipe vide
    } else {
        if (errno == EAGAIN) {
            // Pas de données, on passe à autre chose
            printf("Pas de données disponibles dans le pipe fuel_level_trigger_pipe.\n");
        } else {
            perror("Erreur de lecture dans le pipe fuel_level_trigger_pipe");
        }
    }
}

// Commande l'ouverture ou la fermeture de la vanne d'approvisionnement
void fuel_supply_command(FuelTankManager *fuel_manager, int command) {

    // Commande à la simulation d'ouvrir la vanne d'approvisionnement via le pipe
    if(write(fuel_manager->fuel_supply_pipe[1], &command, sizeof(command)) == -1) {
        perror("Erreur d'écriture dans tank->fuel_supply_pipe \n");
    }

    printf("Fuel Tank Manager : Commande vanne envoyée -> %d \n", command);
}
