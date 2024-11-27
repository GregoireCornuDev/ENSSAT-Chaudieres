#ifndef FUEL_TANK_MANAGER_H
#define FUEL_TANK_MANAGER_H

#include <pthread.h>

// Définition de la structure FuelTankManager
typedef struct {
    float fuel_level; // Niveau de fuel
    int fuel_level_sensor_pipe[2]; // Pipe pour le niveau relevé par le capteur (simulateur)
    int fuel_level_pipe[2]; // Pipe pour le niveau actuel de fuel
    int fuel_level_trigger_pipe[2]; // Pipe pour le déclenchement des capteurs
    int fuel_supply_pipe[2];      // Pipe pour contrôler la vanne d'approvisionnement en eau
    int fuel_use_pipe[2];         // Pipe pour la vanne de sortie (proportionnelle)
    //pthread_mutex_t fuel_level_mutex;
} FuelTankManager;

// Fonction principale du thread
void *fuel_tank_manager_thread(void* arg);

// Initialise le Fuel Tank Manager
void fuel_tank_manager_init();

// S'informe sur le niveau d'eau
void fuel_level_receives(FuelTankManager *tank);

// Transmet le niveau d'eau
void fuel_level_send(FuelTankManager *tank);

// Analyse les déclencheurs des capteurs
void fuel_level_triggers_react(FuelTankManager *tank);

// Commande l'ouverture ou la fermeture de la vanne d'approvisionnement
void fuel_supply_command(FuelTankManager *tank, int command);

#endif // FUEL_TANK_MANAGER_H
