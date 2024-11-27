#include "fuel_tank_simulation.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <asm-generic/errno-base.h>
#include <fcntl.h>    // Pour fcntl() et les constantes comme F_SETFL, O_NONBLOCK

#include "tank_simulation.h"
#include "../config.h"
#include "../mutex_manager.h"

// Thread de la simulation
void *fuel_tank_simulation_thread(void* arg) {
    printf("Fuel Tank Simulation thread started \n");

    TankSimulation *tank_simulation = (void*)arg;

     char *content = "Fuel";
     float fuel_level = START_FUEL_LEVEL;

    // Initialisation du réservoir
    tank_simulation_init(tank_simulation, content, fuel_level);


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
        content_level_update(tank_simulation);

        fuel_level = tank_simulation->content_level;

        // Affichage du niveau d'eau enregistré
        printf("Simulation fuel level: %f \n", fuel_level);

        // Informe le Fuel Tank Manager des triggers
        content_level_sensors_trigger(tank_simulation);

        // Informe le Fuel Tank Manager du niveau d'eau
        content_level_transmit(tank_simulation);

        // S'informe sur l'état de la vanne d'approvisionnement
        supply_valve_open_close(tank_simulation);

        // Renseigne l'état de la vanne d'usage
        usage_valve_control(tank_simulation);
    }
}



