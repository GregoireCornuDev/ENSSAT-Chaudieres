#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "../pipes_manager.h"
#include "../water_tank/water_tank_manager.h"
#include "../central_manager/central_manager.h"
#include "../control_panel/control_panel_manager.h"
#include "../control_panel/gui.h"
#include "tests_pipes.h"

#include <errno.h>

void test_pipes_communication(WaterTankSimulation *simulation, WaterTankManager *tank, CentralManager *central, ControlPanelManager *controlPanel, ControlPanelGUI *gui) {

    // Test de la communication entre les pipes
    float test_value = 42.0;  // Valeur test pour vérifier l'écriture des données
    float read_value = 0.0; // Valeur test pour vérifier la lecture
    float buffer_value = 0.0; // Valeur test pour vérifier la propagation des données

    sleep(5);

    printf("** Analyse écriture ** \n");
    ssize_t bytes_written = write(simulation->water_level_sensor_pipe[1], &test_value, sizeof(test_value));
    if (bytes_written == -1 && errno == EPIPE) {
        printf("Erreur : le côté lecture du pipe est fermé.\n");
    } else if (bytes_written == -1 && errno == EINVAL) {
        printf("Argument invalide \n");
    } else if (bytes_written == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        printf("Pipe est en mode non-bloquant \n");
    } else if (bytes_written == -1 && errno == EBADF) {
        printf("Descripteur invalide \n");
    } else {
        printf("Ecriture OK\n");
    }

    printf("** Analyse lecture ** \n");
    if (read(simulation->water_level_sensor_pipe[0], &read_value, sizeof(read_value)) == -1) {
        perror("Erreur lors de la lecture");
        if (errno == EAGAIN) {
            printf("Le pipe est vide pour le moment (mode non-bloquant).\n");
        } else if (errno == EBADF) {
            printf("Descripteur de fichier invalide ou non ouvert en lecture.\n");
        }
    } else {
        printf("Lecture OK\n") ;
    }


    printf("** Test_pipes_communication : écritures **\n");

    printf("Ecriture sur water_level_sensor_pipe\n");
    fflush(stdout);
    int res = write(simulation->water_level_sensor_pipe[1], &test_value, sizeof(test_value));  // Envoie de la valeur au simulateur
    printf("Résultat : %d\n", res);

    printf("Ecriture sur water_level_pipe\n");
    fflush(stdout);
    res = write(tank->water_level_pipe[1], &test_value, sizeof(test_value));  // Envoie de la valeur au simulateur
    printf("Résultat : %d\n", res);

    printf("Ecriture sur water_average_pipe\n");
    fflush(stdout);
    res = write(central->water_average_pipe[1], &test_value, sizeof(test_value));  // Envoie de la valeur au simulateur
    printf("Résultat : %d\n", res);

    printf("Ecriture sur water_average_gui_pipe\n");
    fflush(stdout);
    res = write(controlPanel->water_average_gui_pipe[1], &test_value, sizeof(test_value));  // Envoie de la valeur au simulateur
    printf("Résultat : %d\n", res);

    sleep(1);

    printf("test_pipes_communication : lectures\n");
    printf("Lecture sur water_level_sensor_pipe\n");
    fflush(stdout);
    read(tank->water_level_sensor_pipe[0], &read_value, sizeof(read_value));
    printf("Lecture sur water_level_pipe\n");
    fflush(stdout);
    read(central->water_level_pipe[0], &read_value, sizeof(read_value));
    printf("Lecture sur water_average_pipe\n");
    fflush(stdout);
    read(controlPanel->water_average_pipe[0], &read_value, sizeof(read_value));
    printf("Lecture sur water_average_gui_pipe\n");
    fflush(stdout);
    read(gui->water_average_gui_pipe[0], &read_value, sizeof(read_value));

    // Test de propagation
    buffer_value = 42.0;


    // Test pour vérifier que le simulateur peut écrire une valeur
    printf("** Test de propagation **\n");

    printf("Envoi d'une valeur depuis le simulateur ...\n");
   if(write(simulation->water_level_sensor_pipe[1], &buffer_value, sizeof(buffer_value)) > 0) {
        printf("Valeur envoyée depuis le simulateur : %f\n", buffer_value);
    } else {
        printf("Erreur lors de l'écriture de la valeur depuis le simulateur.\n");
    }

    sleep(1);  // Attendre un peu pour que le système ait le temps de traiter la donnée

    printf("Réception de la valeur au tank ...\n");
    // Test pour vérifier que le tank peut lire la valeur

    if (read(tank->water_level_sensor_pipe[0], &buffer_value, sizeof(buffer_value)) > 0) {
        printf("Valeur reçue par le tank depuis le simulateur : %f\n", buffer_value);
    } else {
        printf("Erreur lors de la lecture de la valeur depuis le tank.\n");
    }

    buffer_value++;

    printf("Envoi de la valeur depuis le tank ...\n");
    if(write(tank->water_level_pipe[1], &buffer_value, sizeof(buffer_value)) > 0) {
        printf("Valeur envoyée depuis le tank : %f\n", buffer_value);
    } else {
        printf("Erreur lors de l'écriture de la valeur depuis le tank.\n");
    }

    sleep(1);  // Attendre un peu pour que le système ait le temps de traiter la donnée



    // Test pour vérifier que le central peut lire la valeur
    printf("Réception de la valeur au central ...\n");
    if (read(central->water_level_pipe[0], &buffer_value, sizeof(buffer_value)) > 0) {
        printf("Valeur reçue par le manager depuis le simulateur : %f\n", buffer_value);
    } else {
        printf("Erreur lors de la lecture de la valeur depuis le central.\n");
    }

    buffer_value++;

    printf("Envoi de la valeur depuis le central ...\n");
    if(write(central->water_average_pipe[1], &buffer_value, sizeof(buffer_value)) > 0) {
        printf("Valeur envoyée depuis le central : %f\n", buffer_value);
    } else {
        printf("Erreur lors de l'écriture de la valeur depuis le central.\n");
    }

    sleep(1);  // Attendre un peu pour que le système ait le temps de traiter la donnée

    // Test pour vérifier que le central peut lire la valeur
    printf("Réception de la valeur au controlPanel ...\n");
    if (read(controlPanel->water_average_pipe[0], &buffer_value, sizeof(buffer_value)) > 0) {
        printf("Valeur reçue par le controlPanel depuis le central : %f\n", buffer_value);
    } else {
        printf("Erreur lors de la lecture de la valeur depuis le central.\n");
    }

    buffer_value++;

    printf("Envoi de la valeur depuis le controlPanel ...\n");
    if(write(controlPanel->water_average_gui_pipe[1], &buffer_value, sizeof(buffer_value)) > 0) {
        printf("Valeur envoyée depuis le controlPanel : %f\n", buffer_value);
    } else {
        printf("Erreur lors de l'écriture de la valeur depuis le controlPanel.\n");
    }

    sleep(1);  // Attendre un peu pour que le système ait le temps de traiter la donnée

    // Test pour vérifier que le central peut lire la valeur
    printf("Réception de la valeur au GUI ...\n");
    if (read(gui->water_average_gui_pipe[0], &buffer_value, sizeof(buffer_value)) > 0) {
        printf("Valeur reçue par le GUI depuis le controlPanel : %f\n", buffer_value);
    } else {
        printf("Erreur lors de la lecture de la valeur depuis le GUI.\n");
    }



    sleep(1);

    read_value++;


    printf("Test de communication entre les pipes terminé.\n");
}
