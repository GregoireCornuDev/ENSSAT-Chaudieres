#include "mutex_manager.h"

pthread_mutex_t water_level_sensor_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t water_level_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t water_average_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t water_average_gui_mutex = PTHREAD_MUTEX_INITIALIZER;

