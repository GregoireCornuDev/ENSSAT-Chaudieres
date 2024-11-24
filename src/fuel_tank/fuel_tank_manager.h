#ifndef FUEL_TANK_MANAGER_H
#define FUEL_TANK_MANAGER_H

// Définition de la structure WaterTankManager
typedef struct {
    float fuel_level;         // Niveau actuel de l'eau
    int supply_pipe[2];      // Pipe pour la vanne d'approvisionnement
    int use_pipe[2];         // Pipe pour la vanne de sortie (proportionnelle)
} FuelTankManager;

// Fonction principale du thread
void* fuel_tank_manager_thread(void* arg);

#endif // FUEL_TANK_MANAGER_H
