#ifndef WATER_TANK_MANAGER_H
#define WATER_TANK_MANAGER_H

// Définition de la structure WaterTankManager
typedef struct {
    int water_level;         // Niveau actuel de l'eau
    int supply_pipe[2];      // Pipe pour la vanne d'approvisionnement
    int use_pipe[2];         // Pipe pour la vanne de sortie (proportionnelle)
} WaterTankManager;

// Prototypes des fonctions
void* water_tank_manager(void* arg);

#endif // WATER_TANK_MANAGER_H
