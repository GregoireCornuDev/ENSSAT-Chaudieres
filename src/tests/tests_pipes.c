#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "../pipes_manager.h"
#include "water_tank_manager.h"
#include "../central_manager/central_manager.h"
#include "control_panel_manager.h"
#include "tests_pipes.h"

void test_pipes_communication(WaterTankSimulator *simulation, WaterTankManager *manager, CentralManagerData *central, ControlPanelManager *controlPanel) {
    // Test de la communication entre les pipes
    int test_value = 42;  // Valeur test pour vérifier la propagation des données
    int read_value = 0;

    // Test pour vérifier que le simulateur envoie une valeur
    printf("Envoi d'une valeur depuis le simulateur au manager...\n");
    write(simulation->water_sensor_pipe[1], &test_value, sizeof(test_value));  // Envoie de la valeur au manager
    sleep(1);  // Attendre un peu pour que le système ait le temps de traiter la donnée

    // Lire la valeur du pipe dans le gestionnaire de réservoir
    if (read(manager->water_sensor_pipe[0], &read_value, sizeof(read_value)) > 0) {
        printf("Valeur reçue par le manager depuis le simulateur : %d\n", read_value);
    } else {
        printf("Erreur lors de la lecture de la valeur depuis le simulateur.\n");
    }

    // Test pour vérifier que le manager transmet la valeur au central
    printf("Transmission de la valeur du manager au central...\n");
    write(manager->water_level_pipe[1], &read_value, sizeof(read_value));  // Envoie au central
    sleep(1);  // Attendre un peu pour la propagation

    // Lire la valeur dans le central
    if (read(central->water_level_pipe[0], &read_value, sizeof(read_value)) > 0) {
        printf("Valeur reçue par le central depuis le manager : %d\n", read_value);
    } else {
        printf("Erreur lors de la lecture de la valeur depuis le manager.\n");
    }

    // Test pour vérifier que le central transmet la valeur au panneau de contrôle
    printf("Transmission de la valeur du central au panneau de contrôle...\n");
    write(central->water_average_pipe[1], &read_value, sizeof(read_value));  // Envoie au panneau de contrôle
    sleep(1);  // Attendre un peu pour la propagation

    // Lire la valeur dans le panneau de contrôle
    if (read(controlPanel->water_average_pipe[0], &read_value, sizeof(read_value)) > 0) {
        printf("Valeur reçue par le panneau de contrôle depuis le central : %d\n", read_value);
    } else {
        printf("Erreur lors de la lecture de la valeur depuis le central.\n");
    }

    printf("Test de communication entre les pipes terminé.\n");
}
