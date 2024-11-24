#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "central_manager.h"
#include "control_panel_gui.h"
#include "control_panel_config.h"
#include "values_average.h"


// Thread de gestion du panneau de contrôle
void *central_manager_thread(void *arg) {

    printf("Central Manager thread started\n");

    // Cast de l'argument vers le bon type
    CentralManagerData* data = (CentralManagerData*)arg;

    int i;
    while(1)
    {
        // Rien
        i = 0;
    }

    // Vérification que l'argument n'est pas NULL
    if (data == NULL) {
        fprintf(stderr, "Erreur : le pointeur passé au thread est NULL\n");
        pthread_exit(NULL);
    } else {
        printf("Tout va bien\n");
    }

    // Vérification des pipes
    if (data->water_level_pipe[0] == -1 || data->water_level_pipe[1] == -1) {
        fprintf(stderr, "Erreur : pipes pour le niveau d'eau non initialisés correctement\n");
        pthread_exit(NULL);
    }
    printf("Pipes pour le niveau d'eau sont correctement initialisés.\n");

    if (data->water_average_pipe[0] == -1 || data->water_average_pipe[1] == -1) {
        fprintf(stderr, "Erreur : pipes pour la moyenne d'eau non initialisés correctement\n");
        pthread_exit(NULL);
    }
    printf("Pipes pour la moyenne d'eau sont correctement initialisés.\n");

    // Affichage des informations de débogage
    printf("Adresse de data : %p\n", (void *)data);
    printf("Initial water level : %f\n", data->water_level);
    printf("Water pipe read_fd: %d\n", data->water_level_pipe[0]);
    printf("Water pipe write_fd: %d\n", data->water_level_pipe[1]);

    printf("Création du buffer\n");

    ValueBuffer water_buffer;
    create_buffer(&water_buffer, 10);  // 10 est la taille du buffer

    printf("Buffer OK\n");

    float water_level = 0.0;
    float water_average = 0.0;
    float fuel_level = 0.0;
    float fuel_average = 0.0;

    printf("pouet3\n");

    while (1) {

        // Affichage des valeurs avant modification
        printf("\nAvant lecture/écriture:\n");
        printf("Water level: %f\n", water_level);
        printf("Water average: %f\n", water_average);
        printf("Fuel level: %f\n", fuel_level);
        printf("Fuel average: %f\n", fuel_average);

        water_level = data->water_level;
        printf("level OK\n");
        water_average = data->water_average;
        printf("Average OK\n");

        // Affichage des valeurs après modification
        printf("\nAprès lecture/écriture:\n");
        printf("Water level: %f\n", water_level);
        printf("Water average: %f\n", water_average);
        fflush(stdout);

        // Vérification des descripteurs de pipe
        printf("read_fd: %d, write_fd: %d\n", data->water_level_pipe[0], data->water_level_pipe[1]);
        printf("taille du water_level %ld\n", sizeof(water_level));
        fflush(stdout);

        // Vérification que le descripteur de lecture est valide
        if (data->water_level_pipe[0] == -1 || data->water_level_pipe[1] == -1) {
            fprintf(stderr, "-----> Erreur : le descripteur de pipe est invalide\n");
            pthread_exit(NULL);
        } else
        {
            printf("Descripteurs valides\n");
            fflush(stdout);
        }
        // Attendre un peu avant de lire
        sleep(1);

        // Afficher la valeur contenue dans le pipe water_level_pipe à la fin de la fonction
        int pipe_value = 0;
        int res2 = read(data->water_level_pipe[0], &pipe_value, sizeof(pipe_value));
        printf("Res2 est égal à %d", res2);
        if (res2 > 0) {
            printf("Central : Valeur lue depuis water_level_pipe : %d\n", pipe_value);
        } else {
            printf("Central : Erreur de lecture du pipe water_level_pipe\n");
        }
        fflush(stdout);

        // Attendre un peu avant de lire
        sleep(1);

        // Lit le niveau d'eau dans le pipe
        if (read(data->water_level_pipe[0], &water_level, sizeof(water_level)) > 0) {
            printf("Water level received from simulator: %f\n", data->water_level);

            // Calculer la moyenne des niveaux d'eau
            if (water_buffer.count == WATER_TIME_INTERVAL) {

                printf("Ajout de la valeur %f au buffer\n", water_level);
                printf("Buffer count: %d, Buffer index: %d\n", water_buffer.count, water_buffer.index);

                add_values_and_calculate_average(&water_buffer, &data->water_level, WATER_TIME_INTERVAL, &data->water_average);
                printf("Water average over the last %d values: %.2f\n", WATER_TIME_INTERVAL, data->water_average);
            }

            // Envoie au central_manager via son pipe
            write(data->water_average_pipe[1], &data->water_average, sizeof(data->water_average));
            printf("Water level send to control panel: %f\n", data->water_average);
        }

        printf("Moyenne du niveau d'eau sur les 5 derbières secondes : %f\n", data->water_average);

/*
        // Lit le niveau de fuel dans le pipe
        if (read(data->fuel_level_pipe[0], &data->fuel_level, sizeof(&data->fuel_level)) > 0) {
            printf("Fuel level received from simulator: %f\n", data->fuel_level);
            if (fuel_buffer.count == FUEL_TIME_INTERVAL) {
                add_values_and_calculate_average(&fuel_buffer, &data->fuel_level, FUEL_TIME_INTERVAL, &data->fuel_average);
                printf("Fuel average over the last %d values: %.2f\n", FUEL_TIME_INTERVAL, data->fuel_average);
            }

            // Envoie au central_manager via son pipe
            write(data->fuel_average_pipe[1], &data->fuel_average, sizeof(data->fuel_average));
            printf("Fuel level send to control panel: %f", data->fuel_average);

*/
        // Attendre avant la prochaine mise à jour (ex: 1 seconde)
        sleep(1);
    }

    return NULL;
}