#ifndef CENTRAL_MANAGER_H
#define CENTRAL_MANAGER_H

#define WATER_TIME_INTERVAL 5  // Nombre de valeurs à mémoriser pour la moyenne
#define FUEL_TIME_INTERVAL 10  // Nombre de valeurs à mémoriser pour la moyenne

// Structure pour gérer les informations envoyées au panneau de contrôle (GUI)
typedef struct {
    float water_level;   // Niveau d'eau du réservoir
    float water_average;  // Moyenne des valeurs d'eau
    int water_level_pipe[2]; // Pipe pour le niveau actuel de l'eau
    int water_average_pipe[2]; // Pipe pour le niveau actuel de l'eau
    float fuel_level;  // Niveau de carburant du réservoir (si applicable)
    float fuel_average;   // Moyenne des valeurs de carburant
} CentralManagerData;


// Fonction principale du thread
void *central_manager_thread(void *arg);

// Fonction d'initialisation du gestionnaire central
int central_manager_init();

// Fonction de mise à jour des informations (ex: niveau d'eau, niveau de carburant)
void update_control_panel(CentralManagerData *data);

// Fonction de nettoyage du gestionnaire central
void central_manager_cleanup();

#endif // CENTRAL_MANAGER_H
