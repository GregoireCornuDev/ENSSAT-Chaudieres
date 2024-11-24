#ifndef WATER_TANK_MANAGER_H
#define WATER_TANK_MANAGER_H
#include <pthread.h>

// Définition de la structure WaterTankManager
typedef struct {
    int water_sensor_pipe[2]; // Pipe pour le niveau relevé par le capteur (simulateur)
    int water_level_pipe[2]; // Pipe pour le niveau actuel de l'eau
    int supply_pipe[2];      // Pipe pour la vanne d'approvisionnement
    int use_pipe[2];         // Pipe pour la vanne de sortie (proportionnelle)
    pthread_mutex_t water_level_mutex;
} WaterTankManager;

// Fonction principale du thread
void* water_tank_manager_thread(void* arg);

#endif // WATER_TANK_MANAGER_H
