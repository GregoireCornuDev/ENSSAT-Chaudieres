#ifndef FUEL_TANK_SIMULATION_H
#define FUEL_TANK_SIMULATION_H

#include <stdbool.h>

// Définition de la structure FuelTank
typedef struct {
    float fuel_level;         // Niveau actuel du fuel
    int supply_pipe[2];      // Pipe pour contrôler la vanne d'approvisionnement
    int drain_pipe[2];       // Pipe pour contrôler la vanne de sortie
} FuelTanksimulation;

// Fonction principale du thread
void* fuel_tank_simulation_thread(void* arg);

#endif // FUEL_TANK_SIMULATION_H