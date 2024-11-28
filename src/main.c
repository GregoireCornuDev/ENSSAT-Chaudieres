
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // Gestion des pipes
#include "simulation/fuel_tank_simulation.h"
#include "simulation/water_tank_simulation.h"
#include "water_tank/water_tank_manager.h"
#include "fuel_tank/fuel_tank_manager.h"
#include "threads_manager.h"
#include "control_panel/gui.h"
#include "pipes_manager.h"
#include "tests/tests_pipes.h"
#include "config.h"
#include "control_data.h"


int main()
{
    printf("Let's go !\n");

    // Déclarations des structures
    WaterTankSimulation waterSimulation;
    FuelTankSimulation fuelSimulation;
    WaterTankManager waterManager;
    FuelTankManager fuelManager;
    CentralManager centralManager;
    ControlPanelManager controlPanelManager;
    ControlPanelGUI gui;
    ControlData control_data;


    // Démarrer tous les pipes
    setup_water_pipes(&waterSimulation, &waterManager, &centralManager, &controlPanelManager, &gui);
    setup_fuel_pipes(&fuelSimulation, &fuelManager, &centralManager, &controlPanelManager, &gui);

    ThreadList thread_list;
    thread_list_init(&thread_list, 10);

    // Ajouter des threads
    thread_list_add(&thread_list, water_tank_simulation_thread, &waterSimulation);
    thread_list_add(&thread_list, fuel_tank_simulation_thread, &fuelSimulation);
    thread_list_add(&thread_list, water_tank_manager_thread, &waterManager);
    thread_list_add(&thread_list, fuel_tank_manager_thread, &fuelManager);
    thread_list_add(&thread_list, central_manager_thread, &centralManager);
    thread_list_add(&thread_list, control_panel_manager_thread, &controlPanelManager);
    thread_list_add(&thread_list, control_panel_gui_thread, &gui);

    // Démarrer tous les threads
    thread_list_start_all(&thread_list);

    // Tests de DEBUG
    if (MODE_DEBUG == true)
    {
        test_pipes_communication(&waterSimulation, &waterManager, &centralManager, &controlPanelManager, &gui);
    }

    int exit = 0;

    while (1)
    {
        sleep(1);
    }



    // Boucle de simulation simple pour envoyer des commandes aux réservoirs
    printf("Arrêt du programme...\n");

    // Attendre la fin de tous les threads
    thread_list_join_all(&thread_list);

    // Nettoyer les ressources
    thread_list_destroy(&thread_list);



    return 0;
}


