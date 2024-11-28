#include "water_tank_simulation.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <asm-generic/errno-base.h>
#include <fcntl.h>    // Pour fcntl() et les constantes comme F_SETFL, O_NONBLOCK
#include "../config.h"
#include "../mutex_manager.h"

// Thread de la simulation
void *water_tank_simulation_thread(void* arg) {
    printf("Water Tank Simulation thread started \n");

    WaterTankSimulation *simulation = (void*)arg;

    // Initialisation du réservoir
    water_tank_simulation_init(simulation);

    float water_level = 0.0;

    if(MODE_DEBUG == true) {
        // Boucle blanche
        int i;
        while(1) {
            i = 0;
            sleep(1);
        }
    }

    printf("Simulation Eau : Démarrage \n");
    while (1) {

        // Pause de 1 seconde
        sleep(1);

        // Mise à jour du niveau d'eau
        water_level_update(simulation);

        water_level = simulation->water_level;

        // Affichage du niveau d'eau enregistré
        printf("Simulation water level: %f \n", water_level);

        // Informe le Water Tank Manager des triggers
        water_level_sensors_trigger(simulation);

        // Informe le Water Tank Manager du niveau d'eau
        water_level_transmit(simulation);

        // S'informe sur l'état de la vanne d'approvisionnement
        water_supply_valve_open_close(simulation);

        // Renseigne l'état de la vanne d'usage
        water_usage_valve_control(simulation);
    }
}

// Initialise le réservoir
void water_tank_simulation_init(WaterTankSimulation *simulation) {

    simulation->water_level = 40.0f;
    simulation->water_supply_valve = 0;
    simulation->water_use_valve = 0.0f;
    simulation->last_trigger = '0';

    printf("Simulation Eau : Initialisation OK \n");


}

// Transmet le niveau d'eau
void water_level_transmit(WaterTankSimulation *simulation) {

    float water_level = simulation->water_level;

    //pthread_mutex_lock(&water_level_sensor_mutex);
    // Envoie au manager le niveau d'eau via le pipe
    if (write(simulation->water_level_sensor_pipe[1], &water_level, sizeof(water_level)) == -1) {
        perror("Erreur d'écriture dans simulation->water_level_sensor_pipe \n");
    }
    //pthread_mutex_unlock(&water_level_sensor_mutex);
}


// Informe du déclenchement d'un des capteurs
void water_level_sensors_trigger(WaterTankSimulation *simulation) {

    // Récupère le niveau d'eau depuis la struct
    float water_level = simulation->water_level;
    char last_trigger = simulation->last_trigger;

    // Définit un trigger à partir de la mesure du niveau de l'eau
    char new_trigger = water_level_measure(water_level);

    // Si le nouveau trigger est différent
    if (new_trigger != last_trigger) {
        printf("Simulation Eau : Sensors trigger -> nouveau trigger à envoyer : %c \n", new_trigger);

        // Enregistre le dernier trigger effectué dans la struct
        simulation->last_trigger = new_trigger;

        // Transmet l'information au Water Tank Manager via le pipe
        if(write(simulation->water_level_trigger_pipe[1], &new_trigger, sizeof(new_trigger)) == -1) {
            perror("Erreur d'écriture dans simulation->water_level_trigger_pipe \n");
        }
        //printf("Simulation Eau : Sensors trigger -> trigger envoyé : %c \n", new_trigger);

    }
}

// Analyse le niveau de l'eau
char water_level_measure(float water_level) {

    char new_trigger = '0';

    // Analyse le niveau de l'eau (Haute, Basse ou (très) basse)
    if (water_level < 10.0f) {
        new_trigger = 'b'; // Niveau très bas
    } else if (water_level < 30.0f) {
        new_trigger = 'B'; // Niveau bas
    } else if (water_level > 80.0f) {
        new_trigger = 'H'; // Niveau haut
    }
    // Si le niveau d'eau est > 30.0 et < 80.0, new_trigger conserve 'x'

    //printf("Simulation Eau : Sensors trigger -> trigger mesuré : %c \n", new_trigger);

    // Retourne le trigger
    return new_trigger;
}

// S'informe sur l'état de la vanne d'approvisionnement
void water_supply_valve_open_close(WaterTankSimulation *simulation) {

    int open_close_valve = 0;// open = 1 | close = 0

    //printf("Simulation Eau : Vanne d'approvisionnement -> ? \n");

    // Paramètre le pipe comme non bloquant
    int flags = fcntl(simulation->water_supply_pipe[0], F_GETFL, 0);
    fcntl(simulation->water_supply_pipe[0], F_SETFL, flags | O_NONBLOCK);

    // Reçoit l'ordre d'ouvrir ou fermer la vanne d'approvisionnement s'il est présent dans le pipe
    if(read(simulation->water_supply_pipe[0], &open_close_valve, sizeof(open_close_valve)) > 0) {
        printf("Simulation Eau : Vanne d'approvisionnement -> commande reçue : %d \n", open_close_valve);
        simulation->water_supply_valve = open_close_valve;
    // ... sinon, continue sans rien faire
    } else {
        if (errno == EAGAIN) {
            //printf("Simulation Eau : Vanne d'approvisionnement -> pipe water_supply_pipe vide \n");
        } else {
            perror("Erreur de lecture dans simulation->water_supply_pipe \n");
        }
        //printf("Simulation Eau : Vanne d'approvisionnement -> Pas d'action \n");
    }
}

// S'informe sur l'état d'ouverture proportionnel de la vanne d'usage
void water_usage_valve_control(WaterTankSimulation *simulation) {

    float water_use_valve = 0.5f;

    simulation->water_use_valve = water_use_valve;

}

// Met à jour le niveau de l'eau dans le réservoir en fonction de l'ouverture des vannes
void water_level_update(WaterTankSimulation *simulation) {

    float water_level = simulation->water_level;

    // Approvisionnement ouvert/fermé
    if (simulation->water_supply_valve == 0) {

        printf("Simulation Eau : Approvisionnement eau -> fermé \n");

    } else if (simulation->water_supply_valve == 1) {

        printf("Simulation Eau : Approvisionnement eau -> ouvert \n");
        water_level += WATER_FLOW_RATE;

    } else {
        perror("Simulation Eau : Approvisionnement -> Commande inmpossible");
    }

    // Usage proportionnel
    water_level -= simulation->water_use_valve;


    // Met à jour le niveau d'eau dans la structure
    simulation->water_level = water_level;
}


