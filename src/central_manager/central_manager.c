#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "central_manager.h"

#include <unistd.h>

#include "control_panel_gui.h"
#include "control_panel_config.h"

// Déclaration d'une instance pour l'affichage du panneau de contrôle
ControlPanelGUI *panel = NULL;  // Initialisé plus tard dans central_manager_init

// Thread de gestion du panneau de contrôle
void *central_manager_thread(void *arg) {
    CentralManagerData data = {0};  // Initialisation des données

    while (1) {
        // Simuler la récupération des données des réservoirs (exemple avec des valeurs statiques)
        // Dans un cas réel, cela viendrait des réservoirs via un gestionnaire dédié.
        data.water_level = 75;  // Exemple de niveau d'eau
        data.fuel_level = 50.0; // Exemple de niveau de carburant

        // Mise à jour du panneau de contrôle avec ces données
        update_control_panel(&data);

        // Attendre avant la prochaine mise à jour (ex: 1 seconde)
        sleep(1);
    }

    return NULL;
}

// Fonction d'initialisation du gestionnaire central
int central_manager_init() {
    // Initialisation du panneau de contrôle (SDL, textures, etc.)
    panel = control_panel_gui_init(/* SDL_Renderer *renderer */); // Passer un renderer ici
    if (!panel) {
        printf("Erreur lors de l'initialisation du panneau de contrôle\n");
        return -1;
    }

    // Créer un thread pour gérer le flux d'informations vers le panneau de contrôle
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, central_manager_thread, NULL) != 0) {
        printf("Erreur lors de la création du thread de gestion\n");
        return -1;
    }

    return 0;
}

// Fonction de mise à jour des informations du panneau de contrôle
void update_control_panel(CentralManagerData *data) {
    if (panel) {
        // Exemple d'affichage : la jauge de niveau d'eau
        // En fait, tu devras lier ces informations aux éléments du GUI, comme la jauge
        printf("Mise à jour du panneau de contrôle : Niveau d'eau = %d, Niveau de carburant = %.2f\n",
            data->water_level, data->fuel_level);

        // Appel à une fonction pour mettre à jour la jauge de niveau d'eau ou d'autres éléments
        // control_panel_gui_update_gauge(panel, data->water_level);
    }
}

// Fonction de nettoyage
void central_manager_cleanup() {
    if (panel) {
        control_panel_gui_destroy(panel);
    }
    // Nettoyage des autres ressources si nécessaire
}
