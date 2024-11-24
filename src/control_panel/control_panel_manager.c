#include "control_panel_manager.h"
#include <control_panel_gui.h>
#include <stdio.h>
#include <unistd.h>

// Fonction principale du thread
void* control_panel_manager_thread(void* arg) {

    printf("Control Panel Manager Thread Started\n");

    ControlPanelManager* panel = (ControlPanelManager*)arg;
    ControlPanelData data;
    float water_average = 0.0;

    int i;
    while(1)
    {
        // Rien
        i = 0;
    }

    while (1) {
        // Lire la moyenne de l'eau
        if (read(panel->water_average_pipe[0], &water_average, sizeof(water_average)) > 0) {
            printf("Water level received from simulator: %f\n", water_average);
            data.water_average = water_average;
        }

        // Transmettre la donnée au GUI
        if (panel->gui) {
            update_gui(panel->gui, &data); // Mettre à jour l'interface avec les nouvelles données
        }

        sleep(1); // Pause pour éviter un boucle infinie trop rapide
    }

    return NULL;
}

// Fonction pour mettre à jour l'interface avec les nouvelles données
void update_gui(ControlPanelGUI* gui, ControlPanelData* data) {
    if (gui && data) {
        gui->gauge.value = data->water_average;  // Mise à jour de la jauge avec la nouvelle moyenne
        control_panel_gui_render(gui);  // Redessiner le panneau de contrôle avec les nouvelles données
    }
}
