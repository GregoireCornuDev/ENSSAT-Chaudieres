
#ifndef CONTROL_DATA_H
#define CONTROL_DATA_H

// Définition de la structure ControlData
typedef struct {
    float water_average;
    float fuel_average;
    char water_status;
    char fuel_status;
    char co2_status;
    float vapor_pressure_current;
    float vapor_temperature_current;
    float water_temperature_average;
} ControlData;

extern ControlData *CONTROL_DATA;

void CD_init();

void CD_water_average_set(float water_average);

void CD_fuel_average_set(float fuel_average);

void CD_water_status_set(char water_status);

void CD_fuel_status_set(char fuel_status);

void CD_co2_status_set(char co2_status);

void CD_vapor_pressure_current_set(float vapor_pressure_current);

void CD_vapor_temperature_current_set(float vapor_temperature_current);

void CD_water_temperature_average_set(float water_temperature_average);

#endif //CONTROL_DATA_H
