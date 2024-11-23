//
// Created by Grégoire on 18/11/24.
//

#include <stdlib.h>
#include <stdio.h>
#include "water_valve.h"

// Fonction d'initialisation
water_valve* water_valve_create() {
    water_valve* valve = (water_valve*)malloc(sizeof(water_valve));
    if (valve != NULL) {
        valve->state = 0; // Valve fermée par défaut
    }
    return valve;
}

// Méthode pour ouvrir la valve
void water_valve_open(water_valve* valve) {
    if (valve != NULL) {
        valve->state = 1;
        printf("Valve opened.\n");
    }
}

// Méthode pour fermer la valve
void water_valve_close(water_valve* valve) {
    if (valve != NULL) {
        valve->state = 0;
        printf("Valve closed.\n");
    }
}

// Destructor
void water_valve_destroy(water_valve* valve) {
    if (valve != NULL) {
        free(valve);
        printf("Valve destroyed.\n");
    }
}

