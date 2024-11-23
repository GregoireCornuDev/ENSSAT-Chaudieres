//
// Created by Grégoire on 18/11/24.
//
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>


void* thread_water_level(void* arg)
{
    printf("Starting thread_water_level");

    struct sensor_data *data = (struct sensor_data *)arg;

    char buffer;
    int pipe_water_level[2];



    while(true)
    {

        // Attend qu'un octet soit écrit dans le pipe
        read(pipe_water_level[0], &buffer, 1);

        switch (buffer) {
        case 'H':
            printf("HE sensor triggered! Executing...\n");

            // ferme la vanne

            break;
        case 'B':
            printf("BE sensor triggered! Executing...\n");

            // ouvre la vanne

            break;
        case 'b':
            printf("bE sensor triggered! Executing...\n");

            // ouvre vanne + alerte critique

            break;
        default:
            printf("Unknown sensor triggered!\n");
            break;
        }

    return NULL;
    }
}
