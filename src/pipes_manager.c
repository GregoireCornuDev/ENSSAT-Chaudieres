#include <stdio.h>
#include <unistd.h>
#include "pipes_manager.h"

#include <pthread.h>

#include "control_panel_manager.h"
#include "water_tank/water_tank_manager.h"
#include "water_tank/water_tank_simulation.h"
#include "central_manager/central_manager.h"

int setup_water_pipes(WaterTankSimulator *simulation, WaterTankManager *manager, CentralManagerData *central, ControlPanelManager *controlPanel) {

    // Créer le pipe pour le simulateur
    if (pipe(simulation->water_sensor_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_sensor_pipe");
        return -1;
    }

    // Connecter les pipes entre le simulateur et le manager
    manager->water_sensor_pipe[0] = simulation->water_sensor_pipe[0];

    printf("Pipes connectés simulation-manager :\n");
    printf("Simulation: write_fd=%d\n", simulation->water_sensor_pipe[1]);
    printf("Manager: read_fd=%d\n", manager->water_sensor_pipe[0]);

    // Crée le pipe pour le central
    if (pipe(central->water_level_pipe) == -1) {
        perror("Erreur lors de la création du pipe water_sensor_pipe");
        return -1;
    }

    // Connecter les pipes entre le central et le manager
    manager->water_level_pipe[0] = central->water_level_pipe[0];

    printf("Pipes connectés central-manager :\n");
    printf("Simulation: write_fd=%d\n", central->water_level_pipe[1]);
    printf("Manager: read_fd=%d\n", manager->water_level_pipe[0]);


    // Connecter les pipes entre le central et le control
    controlPanel->water_average_pipe[0] = central->water_average_pipe[0];

    printf("Pipes connectés central-control :\n");
    printf("Simulation: write_fd=%d\n", central->water_average_pipe[1]);
    printf("Manager: read_fd=%d\n", controlPanel->water_average_pipe[0]);

    pthread_mutex_init(&manager->water_level_mutex, NULL);


    // Connecter les pipes des vannes
    /*
    // Création des pipes pour les vannes du réservoir d'eau
    if (pipe(water_tank.supply_pipe) == -1 || pipe(water_tank.use_pipe) == -1) {
    perror("Pipe creation failed for water tank");
    return 1;
    }

    // Création des pipes pour les vannes du réservoir de carburant
    if (pipe(fuel_tank.supply_pipe) == -1 || pipe(fuel_tank.use_pipe) == -1) {
    perror("Pipe creation failed for fuel tank");
    return 1;
    }
    */
    return 0;
}


