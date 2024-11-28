#include "control_data.h"

// Définition de la variable globale
ControlData control_data_instance;
ControlData *CONTROL_DATA = &control_data_instance;

void CD_init() {
    CONTROL_DATA->water_average = 0.0f;
    CONTROL_DATA->fuel_average = 0.0f;
    CONTROL_DATA->water_status = '0';
    CONTROL_DATA->fuel_status = '0';
    CONTROL_DATA->co2_status = '0';
    CONTROL_DATA->vapor_pressure_current = 0.0f;
    CONTROL_DATA->vapor_temperature_current  = 0.0f;
    CONTROL_DATA->water_temperature_average = 0.0f;
}



void CD_water_average_set(float water_average) {
    CONTROL_DATA->water_average = water_average;
}

void CD_fuel_average_set(float fuel_average) {
    CONTROL_DATA->fuel_average = fuel_average;
}

void CD_water_status_set(char water_status) {
    CONTROL_DATA->water_status = water_status;
}

void CD_fuel_status_set(char fuel_status) {
    CONTROL_DATA->fuel_status = fuel_status;
}

void CD_co2_status_set(char co2_status) {
    CONTROL_DATA->co2_status = co2_status;}

void CD_vapor_pressure_current_set(float vapor_pressure_current) {
    CONTROL_DATA->vapor_pressure_current = vapor_pressure_current;
}

void CD_vapor_temperature_current_set(float vapor_temperature_current) {
    CONTROL_DATA->vapor_temperature_current = vapor_temperature_current;
}

void CD_water_temperature_average_set(float water_temperature_average) {
    CONTROL_DATA->water_temperature_average = water_temperature_average;
}
