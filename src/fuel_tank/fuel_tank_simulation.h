#ifndef WATER_TANK_SIMULATION_H
#define WATER_TANK_SIMULATION_H

#include <stdbool.h>

// Définition de la structure WaterTank
typedef struct {
    int water_level;         // Niveau actuel de l'eau
    int supply_pipe[2];      // Pipe pour contrôler la vanne d'approvisionnement
    int drain_pipe[2];       // Pipe pour contrôler la vanne de sortie
} WaterTank;

// Prototypes des fonctions
void* water_tank_simulation(void* arg);

#endif // WATER_TANK_SIMULATION_H