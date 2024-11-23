//
// Created by Grégoire on 18/11/24.
//

#ifndef WATER_VALVE_H
#define WATER_VALVE_H

typedef struct {
    int state; // 0 = closed, 1 = open
} water_valve;

// Constructeur
water_valve* water_valve_create();

// Méthodes
void water_valve_open(water_valve* valve);
void water_valve_close(water_valve* valve);
void water_valve_destroy(water_valve* valve);

#endif //WATER_VALVE_H
