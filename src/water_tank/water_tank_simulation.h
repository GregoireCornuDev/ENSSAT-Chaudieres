#ifndef WATER_TANK_SIMULATION_H
#define WATER_TANK_SIMULATION_H

#include <stdbool.h>

// Définition de la structure WaterTankSimulation
typedef struct {
    float water_level;         // Niveau actuel de l'eau
    int water_level_sensor_pipe[2];// Pipe pour le capteur du niveau d'eau (simulateur)
    int water_level_trigger_pipe[2]; // Pipe pour les capteurs par déclenchement
    char last_trigger; // Dernier trigger enregistré
    int water_supply_pipe[2];      // Pipe pour contrôler la vanne d'approvisionnement en eau
    int water_supply_valve; // Etat de la valve d'approvisionnement
    int water_use_pipe[2];       // Pipe pour contrôler la vanne de sortie d'eau
    float water_use_valve; // Etat de la valve d'usage
} WaterTankSimulation;

// Thread de la simulation
void *water_tank_simulation_thread(void* arg);

// Initialise le réservoir
void water_tank_simulation_init(WaterTankSimulation *simulation);

// Transmet le niveau d'eau
void water_level_transmit(WaterTankSimulation *simulation);

// Analyse le niveau de l'eau
char water_level_measure(float water_level);

// Informe du déclenchement d'un des capteurs
void water_level_sensors_trigger(WaterTankSimulation *simulation) ;

// S'informe sur l'état de la vanne d'approvisionnement
void water_supply_valve_open_close(WaterTankSimulation *simulation);

// S'informe sur l'état d'ouverture proportionnel de la vanne d'usage
void water_usage_valve_control(WaterTankSimulation *simulation);

// Met à jour le niveau de l'eau dans le réservoir en fonction de l'ouverture des vannes
void water_level_update(WaterTankSimulation *simulation);

#endif // WATER_TANK_SIMULATION_H