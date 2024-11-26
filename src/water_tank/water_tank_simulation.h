#ifndef WATER_TANK_SIMULATION_H
#define WATER_TANK_SIMULATION_H

#include <stdbool.h>

// Définition de la structure WaterTank
typedef struct {
    int water_level;         // Niveau actuel de l'eau
    int supply_pipe[2];      // Pipe pour contrôler la vanne d'approvisionnement
    int drain_pipe[2];       // Pipe pour contrôler la vanne de sortie
    int water_level_sensor_pipe[2];// Pipe pour le capteur du niveau d'eau (simulateur)
} WaterTankSimulation;

// Prototypes des fonctions
void *water_tank_simulation_thread(void* arg);

WaterTankSimulation *water_tank_simulation_init();

// Initialise le réservoir
void init_water_tank(WaterTankSimulation* tank);

#endif // WATER_TANK_SIMULATION_H