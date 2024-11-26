#include "water_tank_manager.h"

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

        // Receptionne le niveau d'eau depuis le réservoir (simulation)
        water_level_receives(tank);

        water_level = tank->water_level;

        // Affichage du niveau d'eau enregistré
        printf("TankManager water level : %f \n", water_level);

        // Transmet le niveau d'eau au Central Manager
        water_level_send(tank);

        // Analyse les déclencheurs des capteurs et réagit en conséquence (commande les vannes)
        water_level_triggers_react(tank);
    }
}
// Initialise le Water Tank Manager
void water_tank_manager_init(WaterTankManager *tank) {

}

// S'informe sur le niveau d'eau
void water_level_receives(WaterTankManager *tank) {

    float water_level = tank->water_level;

    //pthread_mutex_lock(&water_level_sensor_mutex);
    // Lecture du niveau d'eau envoyé par le simulateur
    if (read(tank->water_level_sensor_pipe[0], &water_level, sizeof(water_level)) == -1) {

        perror("Erreur de lecture dans tank->water_level_sensor_pipe \n");
    }
    //pthread_mutex_unlock(&water_level_sensor_mutex);

    // Enregistre l'information dans la structure
    tank->water_level = water_level;
}

// Transmet le niveau d'eau
void water_level_send(WaterTankManager *tank) {

    float water_level = tank->water_level;

    //pthread_mutex_lock(&water_level_mutex);
    // Ecriture du niveau d'eau à envoyer par le tank manager
    if (write(tank->water_level_pipe[1], &water_level, sizeof(water_level)) == -1) {
        if (errno == EAGAIN) {
            // Pas de données, on passe à autre chose
            printf("Pas de données disponibles dans le pipe water_level_pipe.\n");
        } else {
            perror("Erreur d'écriture dans tank->water_level_pipe \n");
        }

    }
    //pthread_mutex_unlock(&water_level_mutex);
}

// Analyse les déclencheurs des capteurs
void water_level_triggers_react(WaterTankManager *tank) {

    char sensors_trigger = '0';

    // Rend le pip non bloquant
    int flags = fcntl(tank->water_level_trigger_pipe[0], F_GETFL, 0);
    fcntl(tank->water_level_trigger_pipe[0], F_SETFL, flags | O_NONBLOCK);

    // Reçoit le déclenchement des capteurs
    if(read(tank->water_level_trigger_pipe[0], &sensors_trigger, sizeof(sensors_trigger)) > 0) {
        printf("Trigger : %c \n", sensors_trigger);

        if(sensors_trigger == 'H') {
            // Commande l'ouverture de la vanne d'approvisionnement
            water_supply_command(tank, 0);
            printf("Fermeture de la vanne d'approvisionnement en eau \n");
        } else if (sensors_trigger == 'B') {
            // Commande la fermeture de la vanne d'approvisionnement
            water_supply_command(tank, 1);
            printf("Ouverture de la vanne d'approvisionnement en eau \n");
        } else if (sensors_trigger == 'b') {
            // Commande la fermeture de la vanne d'approvisionnement
            water_supply_command(tank, 1);
            // Déclenche une alerte critique
            printf("Ouverture de la vanne d'approvisionnement en eau et alerte \n");
        } else {
            perror("Message sensors trigger non reconnu \n");
        }

    // Pipe vide
    } else {
        if (errno == EAGAIN) {
            // Pas de données, on passe à autre chose
            printf("Pas de données disponibles dans le pipe water_level_trigger_pipe.\n");
        } else {
            perror("Erreur de lecture dans le pipe water_level_trigger_pipe");
        }
    }
}

// Commande l'ouverture ou la fermeture de la vanne d'approvisionnement
void water_supply_command(WaterTankManager *tank, int command) {

    // Commande à la simulation d'ouvrir la vanne d'approvisionnement via le pipe
    if(write(tank->water_supply_pipe[1], &command, sizeof(command)) == -1) {
        perror("Erreur d'écriture dans tank->water_supply_pipe \n");
    }

    printf("Water Tank Manager : Commande vanne envoyée -> %d \n", command);
}
