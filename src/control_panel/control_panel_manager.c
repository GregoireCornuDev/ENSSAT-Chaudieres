#include "gui.h"
#include "control_panel_manager.h"
#include "control_data.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "../config.h"

// Fonction principale du thread
void *control_panel_manager_thread(void* arg) {

    printf("Control Panel Manager Thread Started\n");

    ControlPanelManager *panel = (void*)arg;//control_panel_manager_init();

    float water_average = 0.0;
    float fuel_average = 0.0;

    if(MODE_DEBUG == true) {
        // Boucle blanche
        int i;
        while(1) {
            i = 0;
            sleep(1);
        }
    }

    while (1) {

        /** WATER */
        // Lecture du niveau d'eau moyen envoyé par le central manager
        if (read(panel->water_average_pipe[0], &water_average, sizeof(water_average)) > 0) {
            CD_water_average_set(water_average);
            // Met à jour la data dans CONTROL_DATA
        } else {
            perror("Erreur de lecture dans panel->water_average_pipe \n");
        }
        panel->water_average = water_average;

        // Affichage du niveau d'eau moyen enregistré
        printf("ControlPanel water average : %f \n", water_average);

        // Ecriture du niveau d'eau à envoyer au GUI

        /*
        if (write(panel->water_average_gui_pipe[1], &water_average, sizeof(water_average)) == -1) {
            perror("Erreur d'écriture dans panel->water_average_gui_pipe \n");
        }
        */

        /** FUEL */
        // Lecture du niveau de fuel moyen envoyé par le central manager
        if (read(panel->fuel_average_pipe[0], &fuel_average, sizeof(fuel_average)) > 0) {
            // Met à jour la data dans CONTROL_DATA
            CD_fuel_average_set(fuel_average);
        } else {
            perror("Erreur de lecture dans panel->fuel_average_pipe \n");
        }
        panel->water_average = water_average;

        // Affichage du niveau de fuel moyen enregistré
        printf("ControlPanel fuel average : %f \n", water_average);

        // Ecriture du niveau de fuel à envoyer au GUI
        /*
        if (write(panel->fuel_average_gui_pipe[1], &fuel_average, sizeof(fuel_average)) == -1) {
            perror("Erreur d'écriture dans panel->water_average_gui_pipe \n");

        }
        */
    }
}

ControlPanelManager *control_panel_manager_init() {
    ControlPanelManager *control_panel_manager = (ControlPanelManager*)malloc(sizeof(ControlPanelManager));

    // Initialise le niveau d'eau moyen
    control_panel_manager->water_average = 0.0;

    return control_panel_manager;
}


