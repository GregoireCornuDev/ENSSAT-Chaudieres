#include "fuel_tank_simulation.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <asm-generic/errno-base.h>
#include <fcntl.h>    // Pour fcntl() et les constantes comme F_SETFL, O_NONBLOCK

#include "fuel_tank_simulation.h"
#include "../config.h"
#include "../mutex_manager.h"

// Thread de la simulation
void *fuel_tank_simulation_thread(void* arg) {
    printf("Fuel Tank Simulation thread started \n");

    FuelTankSimulation *fuel_tank_simulation = (void*)arg;

     char *fuel = "Fuel";
     float fuel_level = START_FUEL_LEVEL;

    // Initialisation du réservoir
    fuel_tank_simulation_init(fuel_tank_simulation, fuel_level);


    if(MODE_DEBUG == true) {
        // Boucle blanche
        int i;
        while(1) {
            i = 0;
            sleep(1);
        }
    }

    printf("Simulation Fuel : Démarrage \n");
    while (1) {

        // Pause de 1 seconde
        sleep(1);

        // Mise à jour du niveau de fuel
        fuel_level_update(fuel_tank_simulation);

        fuel_level = fuel_tank_simulation->fuel_level;

        // Affichage du niveau d'eau enregistré
        printf("Simulation fuel level: %f \n", fuel_level);

        // Informe le Fuel Tank Manager des triggers
        fuel_level_sensors_trigger(fuel_tank_simulation);

        // Informe le Fuel Tank Manager du niveau d'eau
        fuel_level_transmit(fuel_tank_simulation);

        // S'informe sur l'état de la vanne d'approvisionnement
        fuel_supply_valve_open_close(fuel_tank_simulation);

        // Renseigne l'état de la vanne d'usage
        fuel_usage_valve_control(fuel_tank_simulation);
    }
}

// Initialise le réservoir
void fuel_tank_simulation_init(FuelTankSimulation *fuel_tank_simulation, float fuel_level) {

    fuel_tank_simulation->fuel_level = fuel_level;
    fuel_tank_simulation->fuel_supply_valve = 0;
    fuel_tank_simulation->fuel_use_valve1 = 0.0f;
    fuel_tank_simulation->fuel_use_valve2 = 0.0f;
    fuel_tank_simulation->last_trigger = '0';

    printf("Simulation Tank Fuel : Initialisation OK \n");


}

// Transmet le niveau de fuel
void fuel_level_transmit(FuelTankSimulation *fuel_tank_simulation) {

    float fuel_level = fuel_tank_simulation->fuel_level;

    // Envoie au manager le niveau d'eau via le pipe
    //pthread_mutex_lock(&fuel_level_sensor_mutex);

    if (write(fuel_tank_simulation->fuel_level_sensor_pipe[1], &fuel_level, sizeof(fuel_level)) == -1) {
        perror("Erreur d'écriture dans simulation->fuel_level_sensor_pipe \n");
    }
    //pthread_mutex_unlock(&fuel_level_sensor_mutex);
}


// Informe du déclenchement d'un des capteurs
void fuel_level_sensors_trigger(FuelTankSimulation *fuel_tank_simulation) {

    // Récupère le niveau de fuel depuis la struct
    float fuel_level = fuel_tank_simulation->fuel_level;
    char last_trigger = fuel_tank_simulation->last_trigger;

    // Définit un trigger à partir de la mesure du niveau de fuel
    char new_trigger = fuel_level_measure(fuel_level);

    // Si le nouveau trigger est différent
    if (new_trigger != last_trigger) {
        printf("Simulation Fuel : Sensors trigger -> nouveau trigger à envoyer : %c \n", new_trigger);

        // Enregistre le dernier trigger effectué dans la struct
        fuel_tank_simulation->last_trigger = new_trigger;

        // Transmet l'information au Fuel Tank Manager via le pipe
        if(write(fuel_tank_simulation->fuel_level_trigger_pipe[1], &new_trigger, sizeof(new_trigger)) == -1) {
            perror("Erreur d'écriture dans simulation->fuel_level_trigger_pipe \n");
        }
        printf("Simulation Fuel : Sensors trigger -> trigger envoyé : %c \n", new_trigger);

    }
}

// Analyse le niveau de fuel
char fuel_level_measure(float fuel_level) {

    char new_trigger = '0';

    // Analyse le niveau de fuel (Haute, Basse ou (très) basse)
    if (fuel_level < 10.0f) {
        new_trigger = 'b'; // Niveau très bas
    } else if (fuel_level < 30.0f) {
        new_trigger = 'B'; // Niveau bas
    } else if (fuel_level > 80.0f) {
        new_trigger = 'H'; // Niveau haut
    }
    // Si le niveau de fuel est > 30.0 et < 80.0, new_trigger conserve 'x'

    printf("Simulation : Sensors trigger -> trigger mesuré : %c \n", new_trigger);

    // Retourne le trigger
    return new_trigger;
}

// S'informe sur l'état de la vanne d'approvisionnement
void fuel_supply_valve_open_close(FuelTankSimulation *fuel_tank_simulation) {

    int open_close_valve = 0;// open = 1 | close = 0


    //printf("Simulation Fuel : Vanne d'approvisionnement -> ? \n");

    // Paramètre le pipe comme non bloquant
    int flags = fcntl(fuel_tank_simulation->fuel_supply_pipe[0], F_GETFL, 0);
    fcntl(fuel_tank_simulation->fuel_supply_pipe[0], F_SETFL, flags | O_NONBLOCK);

    // Reçoit l'ordre d'ouvrir ou fermer la vanne d'approvisionnement s'il est présent dans le pipe
    if(read(fuel_tank_simulation->fuel_supply_pipe[0], &open_close_valve, sizeof(open_close_valve)) > 0) {

        printf("Simulation Fuel : Vanne d'approvisionnement -> commande reçue : %d \n", open_close_valve);
        fuel_tank_simulation->fuel_supply_valve = open_close_valve;

    // ... sinon, continue sans rien faire
    } else {
        if (errno == EAGAIN) {
            //printf("Simulation %c : Vanne d'approvisionnement -> pipe fuel_supply_pipe vide \n", *fuel);
        } else {
            perror("Erreur de lecture dans simulation->fuel_supply_pipe \n");
        }
        //printf("Simulation Fuel : Vanne d'approvisionnement -> Pas d'action \n");
    }
}

// S'informe sur l'état d'ouverture proportionnel de la vanne d'usage
void fuel_usage_valve_control(FuelTankSimulation *fuel_tank_simulation) {

    float fuel_use_valve = 0.5f;

    fuel_tank_simulation->fuel_use_valve1 = fuel_use_valve;

}

// Met à jour le niveau de fuel dans le réservoir en fonction de l'ouverture des vannes
void fuel_level_update(FuelTankSimulation *fuel_tank_simulation) {

    float fuel_level = fuel_tank_simulation->fuel_level;

    // Approvisionnement ouvert/fermé
    if (fuel_tank_simulation->fuel_supply_valve == 0) {

        printf("Simulation Fuel : Approvisionnement eau -> fermé \n");

    } else if (fuel_tank_simulation->fuel_supply_valve == 1) {

        printf("Simulation Fuel : Approvisionnement eau -> ouvert \n");
        fuel_level += WATER_FLOW_RATE;

    } else {
        printf("Simulation Fuel : ");
        perror("Approvisionnement -> Commande inmpossible");

    }

    // Usage proportionnel
    fuel_level -= fuel_tank_simulation->fuel_use_valve1;
    // Usage 0.0 ou 0.5 ou 1.0
    fuel_level -= fuel_tank_simulation->fuel_use_valve2;

    // Met à jour le niveau dd fuel dans la structure
    fuel_tank_simulation->fuel_level = fuel_level;
}



