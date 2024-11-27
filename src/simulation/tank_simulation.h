#ifndef TANK_SIMULATION_H
#define TANK_SIMULATION_H

// Définition de la structure de TankSimulation
typedef struct {
    char *content;
    float content_level;                 // Niveau actuel du contenu
    int content_level_sensor_pipe[2];    // Pipe pour le capteur du niveau dde contenu
    int content_level_trigger_pipe[2];   // Pipe pour les capteurs par déclenchement
    char last_trigger;                   // Dernier trigger enregistré
    int content_supply_pipe[2];          // Pipe pour contrôler la vanne d'approvisionnement
    int content_supply_valve;            // Etat de la valve d'approvisionnement
    int content_use_pipe[2];             // Pipe pour contrôler la vanne de sortie d'usage
    float content_use_valve;             // Etat de la valve d'usage
} TankSimulation;

// Thread de la simulation
//void *tank_simulation_thread(void* arg);

// Initialise le réservoir
void tank_simulation_init(TankSimulation *tank_simulation, char *content, float content_level);

// Transmet le niveau du contenu
void content_level_transmit(TankSimulation *tank_simulation);

// Analyse le niveau du contenu
char content_level_measure(float content_level);

// Informe du déclenchement d'un des capteurs
void content_level_sensors_trigger(TankSimulation *tank_simulation) ;

// S'informe sur l'état de la vanne d'approvisionnement
void supply_valve_open_close(TankSimulation *tank_simulation);

// S'informe sur l'état d'ouverture proportionnel de la vanne d'usage
void usage_valve_control(TankSimulation *tank_simulation);

// Met à jour le niveau de l'eau dans le réservoir en fonction de l'ouverture des vannes
void content_level_update(TankSimulation *tank_simulation);

#endif //TANK_SIMULATION_H
