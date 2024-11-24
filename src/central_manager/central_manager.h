#ifndef CENTRAL_MANAGER_H
#define CENTRAL_MANAGER_H

// Structure pour gérer les informations envoyées au panneau de contrôle (GUI)
typedef struct {
    int water_level;   // Niveau d'eau du réservoir
    float fuel_level;  // Niveau de carburant du réservoir (si applicable)
} CentralManagerData;

// Fonction d'initialisation du gestionnaire central
int central_manager_init();

// Fonction de gestion des threads
void *central_manager_thread(void *arg);

// Fonction de mise à jour des informations (ex: niveau d'eau, niveau de carburant)
void update_control_panel(CentralManagerData *data);

// Fonction de nettoyage du gestionnaire central
void central_manager_cleanup();

#endif // CENTRAL_MANAGER_H
