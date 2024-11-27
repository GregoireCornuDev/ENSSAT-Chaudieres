#include <stdio.h>
#include <unistd.h>
#include "pipes_manager.h"
#include <pthread.h>
#include "control_panel_manager.h"
#include "water_tank/water_tank_manager.h"
#include "water_tank/water_tank_simulation.h"
#include "central_manager/central_manager.h"
#include "fuel_tank/fuel_tank_manager.h"
#include "simulation/tank_simulation.h"

int setup_water_pipes(WaterTankSimulation *simulation, WaterTankManager *tank, CentralManager *central, ControlPanelManager *controlPanel, ControlPanelGUI *gui) {

    /** WATER LEVEL SENSOR - AVERAGE */
    // Pipe pour le simulateur -> tank
    if (pipe(simulation->water_level_sensor_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_level_sensor_pipe");
        return -1;
    }
    // Le simulateur écrit dans [1], le tank lit dans [0]
    tank->water_level_sensor_pipe[0] = simulation->water_level_sensor_pipe[0];
    tank->water_level_sensor_pipe[1] = simulation->water_level_sensor_pipe[1];

    // Vérification des descripteurs
    if (simulation->water_level_sensor_pipe[0] == -1 || simulation->water_level_sensor_pipe[1] == -1 || tank->water_level_sensor_pipe[0] == -1 || tank->water_level_sensor_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe water_level_sensor_pipe est invalide");
        return -1;
    }

    // Pipe pour le tank -> central
    if (pipe(tank->water_level_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_level_pipe");
        return -1;
    }
    // Le tank écrit dans [1], le central lit dans [0]
    central->water_level_pipe[0] = tank->water_level_pipe[0];
    central->water_level_pipe[1] = tank->water_level_pipe[1];

    // Vérification des descripteurs
    if (tank->water_level_pipe[0] == -1 || tank->water_level_pipe[1] == -1 || central->water_level_pipe[0] == -1 || central->water_level_pipe[1] == -1) {
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

    /** WATER LEVEL TRIGGER */
    // Pipe pour le simulateur -> tank
    if (pipe(simulation->water_level_trigger_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_level_trigger_pipe");
        return -1;
    }
    // Le simulateur écrit dans [1], le tank lit dans [0]
    tank->water_level_trigger_pipe[0] = simulation->water_level_trigger_pipe[0];
    tank->water_level_trigger_pipe[1] = simulation->water_level_trigger_pipe[1];

    // Vérification des descripteurs
    if (simulation->water_level_trigger_pipe[0] == -1 || simulation->water_level_trigger_pipe[1] == -1 || tank->water_level_trigger_pipe[0] == -1 || tank->water_level_trigger_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe water_level_sensor_pipe est invalide");
        return -1;
    }

    /** WATER SUPPLY */

    // Pipe pour le tank -> simulation
    if (pipe(tank->water_supply_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_supply_pipe");
        return -1;
    }
    // Le tank écrit dans [1], la simulation lit dans [0]
    simulation->water_supply_pipe[0] = tank->water_supply_pipe[0];
    simulation->water_supply_pipe[1] = tank->water_supply_pipe[1];

    // Vérification des descripteurs
    if (simulation->water_supply_pipe[0] == -1 || simulation->water_supply_pipe[1] == -1 || tank->water_supply_pipe[0] == -1 || tank->water_supply_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe water_supply_pipe est invalide");
        return -1;
    }



    printf("Setup des pipes OK \n");

    return 0;
}

int setup_fuel_pipes(TankSimulation *simulation, FuelTankManager *fuel_manager, CentralManager *central_manager, ControlPanelManager *control_manager, ControlPanelGUI *gui) {

    /** WATER LEVEL SENSOR - AVERAGE */
    // Pipe pour le simulateur -> tank
    if (pipe(simulation->content_level_sensor_pipe) == -1) {
        perror("Erreur lors de la création du pipe fuel_level_sensor_pipe");
        return -1;
    }
    // Le simulateur écrit dans [1], le tank lit dans [0]
    fuel_manager->fuel_level_sensor_pipe[0] = simulation->content_level_sensor_pipe[0];
    fuel_manager->fuel_level_sensor_pipe[1] = simulation->content_level_sensor_pipe[1];

    // Vérification des descripteurs
    if (simulation->content_level_sensor_pipe[0] == -1 || simulation->content_level_sensor_pipe[1] == -1 || fuel_manager->fuel_level_sensor_pipe[0] == -1 || fuel_manager->fuel_level_sensor_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe fuel_level_sensor_pipe est invalide");
        return -1;
    }

    // Pipe pour le tank -> central
    if (pipe(fuel_manager->fuel_level_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_level_pipe");
        return -1;
    }
    // Le tank écrit dans [1], le central lit dans [0]
    central_manager->fuel_level_pipe[0] = fuel_manager->fuel_level_pipe[0];
    central_manager->fuel_level_pipe[1] = fuel_manager->fuel_level_pipe[1];

    // Vérification des descripteurs
    if (fuel_manager->fuel_level_pipe[0] == -1 || fuel_manager->fuel_level_pipe[1] == -1 || central_manager->fuel_level_pipe[0] == -1 || central_manager->fuel_level_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe fuel_level_pipe est invalide");
        return -1;
    }

    // Pipe pour le central -> controlPanel
    if (pipe(central_manager->fuel_average_pipe) == -1) {
        perror("Erreur lors de la création du pipe fuel_average_pipe");
        return -1;
    }
    // Le central écrit dans [1], le control panel lit dans [0]
    control_manager->fuel_average_pipe[0] = central_manager->fuel_average_pipe[0];
    control_manager->fuel_average_pipe[1] = central_manager->fuel_average_pipe[1];

    // Vérification des descripteurs
    if (central_manager->fuel_average_pipe[0] == -1 || central_manager->fuel_average_pipe[1] == -1 || control_manager->fuel_average_pipe[0] == -1 || control_manager->fuel_average_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe fuel_average_pipe est invalide");
        return -1;
    }

    // Pipe pour le controlPanel -> GUI
    if (pipe(control_manager->fuel_average_gui_pipe) == -1) {
        perror("Erreur lors de la création du pipe fuel_average_gui_pipe");
        return -1;
    }
    // Le controlPanel écrit dans [1], le GUI lit dans [0]
    gui->fuel_average_gui_pipe[0] = control_manager->fuel_average_gui_pipe[0];
    gui->fuel_average_gui_pipe[1] = control_manager->fuel_average_gui_pipe[1];

    // Vérification des descripteurs
    if (central_manager->fuel_average_pipe[0] == -1 || central_manager->fuel_average_pipe[1] == -1 || control_manager->fuel_average_pipe[0] == -1 || control_manager->fuel_average_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe fuel_average_gui_pipe est invalide");
        return -1;
    }

    /** WATER LEVEL TRIGGER */
    // Pipe pour le simulateur -> tank
    if (pipe(simulation->content_level_trigger_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_level_trigger_pipe");
        return -1;
    }
    // Le simulateur écrit dans [1], le tank lit dans [0]
    fuel_manager->fuel_level_trigger_pipe[0] = simulation->content_level_trigger_pipe[0];
    fuel_manager->fuel_level_trigger_pipe[1] = simulation->content_level_trigger_pipe[1];

    // Vérification des descripteurs
    if (simulation->content_level_trigger_pipe[0] == -1 || simulation->content_level_trigger_pipe[1] == -1 || fuel_manager->fuel_level_trigger_pipe[0] == -1 || fuel_manager->fuel_level_trigger_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe water_level_sensor_pipe est invalide");
        return -1;
    }

    /** FUEL SUPPLY */

    // Pipe pour le tank -> simulation
    if (pipe(fuel_manager->fuel_supply_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_supply_pipe");
        return -1;
    }
    // Le tank écrit dans [1], la simulation lit dans [0]
    simulation->content_supply_pipe[0] = fuel_manager->fuel_supply_pipe[0];
    simulation->content_supply_pipe[1] = fuel_manager->fuel_supply_pipe[1];

    // Vérification des descripteurs
    if (simulation->content_supply_pipe[0] == -1 || simulation->content_supply_pipe[1] == -1 || fuel_manager->fuel_supply_pipe[0] == -1 || fuel_manager->fuel_supply_pipe[1] == -1) {
        perror("Erreur : l'un des descripteurs de fichiers du pipe water_supply_pipe est invalide");
        return -1;
    }



    printf("Setup des pipes OK \n");

    return 0;
}
