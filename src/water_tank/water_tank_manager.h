#ifndef WATER_TANK_MANAGER_H
#define WATER_TANK_MANAGER_H
#include <pthread.h>

// Définition de la structure WaterTankManager
typedef struct {
    float water_level; // Niveau de l'eau
    int water_level_sensor_pipe[2]; // Pipe pour le niveau relevé par le capteur (simulateur)
    int water_level_pipe[2]; // Pipe pour le niveau actuel de l'eau
    int water_level_trigger_pipe[2]; // Pipe pour le déclenchement des capteurs
    int water_supply_pipe[2];      // Pipe pour contrôler la vanne d'approvisionnement en eau
    int water_use_pipe[2];         // Pipe pour la vanne de sortie (proportionnelle)
    //pthread_mutex_t water_level_mutex;
} WaterTankManager;

// Fonction principale du thread
void *water_tank_manager_thread(void* arg);

// Initialise le Water Tank Manager
void water_tank_manager_init();

// S'informe sur le niveau d'eau
void water_level_receives(WaterTankManager *tank);

// Transmet le niveau d'eau
void water_level_send(WaterTankManager *tank);

// Analyse les déclencheurs des capteurs
void water_level_triggers_react(WaterTankManager *tank);

// Commande l'ouverture ou la fermeture de la vanne d'approvisionnement
void water_supply_command(WaterTankManager *tank, int command);

#endif // WATER_TANK_MANAGER_H
