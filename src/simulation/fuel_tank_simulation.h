#ifndef FUEL_TANK_SIMULATION_H
#define FUEL_TANK_SIMULATION_H

#include <stdbool.h>

// Définition de la structure de FuelTankSimulation
typedef struct {
    float fuel_level;                 // Niveau actuel du fuel
    int fuel_level_sensor_pipe[2];    // Pipe pour le capteur du niveau de fuel
    int fuel_level_trigger_pipe[2];   // Pipe pour les capteurs par déclenchement
    char last_trigger;                   // Dernier trigger enregistré
    int fuel_supply_pipe[2];          // Pipe pour contrôler la vanne d'approvisionnement
    int fuel_supply_valve;            // Etat de la valve d'approvisionnement
    int fuel_use_pipe1[2];             // Pipe pour contrôler la vanne de sortie d'usage
    float fuel_use_valve1;             // Etat de la valve d'usage
    int fuel_use_pipe2[2];             // Pipe pour contrôler la vanne de sortie d'usage
    float fuel_use_valve2;             // Etat de la valve d'usage
} FuelTankSimulation;

// Thread de la simulation
void *fuel_tank_simulation_thread(void* arg);

// Initialise le réservoir
void fuel_tank_simulation_init(FuelTankSimulation *fuel_tank_simulation, float fuel_level);

// Transmet le niveau du contenu
void fuel_level_transmit(FuelTankSimulation *fuel_tank_simulation);

// Analyse le niveau du contenu
char fuel_level_measure(float fuel_level);

// Informe du déclenchement d'un des capteurs
void fuel_level_sensors_trigger(FuelTankSimulation *fuel_tank_simulation) ;

// S'informe sur l'état de la vanne d'approvisionnement
void fuel_supply_valve_open_close(FuelTankSimulation *fuel_tank_simulation);

// S'informe sur l'état d'ouverture proportionnel de la vanne d'usage
void fuel_usage_valve_control(FuelTankSimulation *fuel_tank_simulation);

// Met à jour le niveau de l'eau dans le réservoir en fonction de l'ouverture des vannes
void fuel_level_update(FuelTankSimulation *fuel_tank_simulation);


#endif // FUEL_TANK_SIMULATION_H