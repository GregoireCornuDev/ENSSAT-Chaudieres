#include "thread_manager.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "water_tank_manager.h"

// Fonction pour créer et démarrer tous les threads
int start_threads(WaterTankManager* reservoir) {
    // Création des threads pour le réservoir d'eau
    pthread_t water_tank_thread, water_supply_thread, water_use_thread;

    // Thread pour la gestion du réservoir d'eau
    if (pthread_create(&reservoir_thread, NULL, reservoir_manager, reservoir) != 0) {
        perror("Failed to create reservoir manager thread");
        return 1;
    }

    // Thread pour contrôler la vanne d'approvisionnement
    if (pthread_create(&supply_thread, NULL, valve_controller, reservoir->supply_pipe) != 0) {
        perror("Failed to create supply thread");
        return 1;
    }

    // Thread pour contrôler la vanne d'utilisation (proportionnelle)
    if (pthread_create(&use_thread, NULL, valve_controller, reservoir->use_pipe) != 0) {
        perror("Failed to create use thread");
        return 1;
    }

    // Attente de la fin des threads
    pthread_join(supply_thread, NULL);
    pthread_join(use_thread, NULL);
    pthread_cancel(reservoir_thread); // Force l'arrêt du thread de gestion du réservoir
    pthread_join(reservoir_thread, NULL);

    return 0;
}
