#include <stdio.h>
#include <unistd.h>
#include "pipes_manager.h"
#include <pthread.h>
#include "control_panel_manager.h"
#include "water_tank/water_tank_manager.h"
#include "water_tank/water_tank_simulation.h"
#include "central_manager/central_manager.h"

int setup_water_pipes(WaterTankSimulation *simulation, WaterTankManager *manager, CentralManager *central, ControlPanelManager *controlPanel, ControlPanelGUI *gui) {

    // Pipe pour le simulateur -> manager
    if (pipe(simulation->water_level_sensor_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_level_sensor_pipe");
        return -1;
    }
    // Le simulateur écrit dans [1], le manager lit dans [0]
    manager->water_level_sensor_pipe[0] = simulation->water_level_sensor_pipe[0];
    manager->water_level_sensor_pipe[1] = simulation->water_level_sensor_pipe[1];

    // Vérification des descripteurs
    if (simulation->water_level_sensor_pipe[0] == -1 || simulation->water_level_sensor_pipe[1] == -1 || manager->water_level_sensor_pipe[0] == -1 || manager->water_level_sensor_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe water_level_sensor_pipe est invalide");
        return -1;
    }

    // Pipe pour le manager -> central
    if (pipe(manager->water_level_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_level_pipe");
        return -1;
    }
    // Le manager écrit dans [1], le central lit dans [0]
    central->water_level_pipe[0] = manager->water_level_pipe[0];
    central->water_level_pipe[1] = manager->water_level_pipe[1];

    // Vérification des descripteurs
    if (manager->water_level_pipe[0] == -1 || manager->water_level_pipe[1] == -1 || central->water_level_pipe[0] == -1 || central->water_level_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe water_level_pipe est invalide");
        return -1;
    }

    // Pipe pour le central -> controlPanel
    if (pipe(central->water_average_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_average_pipe");
        return -1;
    }
    // Le central écrit dans [1], le control panel lit dans [0]
    controlPanel->water_average_pipe[0] = central->water_average_pipe[0];
    controlPanel->water_average_pipe[1] = central->water_average_pipe[1];

    // Vérification des descripteurs
    if (central->water_average_pipe[0] == -1 || central->water_average_pipe[1] == -1 || controlPanel->water_average_pipe[0] == -1 || controlPanel->water_average_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe water_average_pipe est invalide");
        return -1;
    }

    // Pipe pour le controlPanel -> GUI
    if (pipe(controlPanel->water_average_gui_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_average_gui_pipe");
        return -1;
    }
    // Le controlPanel écrit dans [1], le GUI lit dans [0]
    gui->water_average_gui_pipe[0] = controlPanel->water_average_gui_pipe[0];
    gui->water_average_gui_pipe[1] = controlPanel->water_average_gui_pipe[1];

    // Vérification des descripteurs
    if (central->water_average_pipe[0] == -1 || central->water_average_pipe[1] == -1 || controlPanel->water_average_pipe[0] == -1 || controlPanel->water_average_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe water_average_gui_pipe est invalide");
        return -1;
    }

    printf("Setup des pipes OK \n");

    return 0;
}
