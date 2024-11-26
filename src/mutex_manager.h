//
// Created by gregoire on 26/11/24.
//

#ifndef MUTEX_MANAGER_H
#define MUTEX_MANAGER_H

#include <pthread.h>

// Déclaration du mutex global
extern pthread_mutex_t water_level_sensor_mutex;
extern pthread_mutex_t water_level_mutex;
extern pthread_mutex_t water_average_mutex;
extern pthread_mutex_t water_average_gui_mutex;

#endif //MUTEX_MANAGER_H
