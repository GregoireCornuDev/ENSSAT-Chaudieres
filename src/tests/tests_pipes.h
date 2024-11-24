#ifndef TEST_PIPES_H
#define TEST_PIPES_H

#include "water_tank_manager.h"
#include "../central_manager/central_manager.h"
#include "control_panel_manager.h"
#include "water_tank_simulation.h"

/**
 * Fonction pour tester la communication via les pipes.
 * Vérifie que les pipes peuvent être correctement lus et que l'information se propage de l'un à l'autre.
 */
void test_pipes_communication(WaterTankSimulator *simulation,
                               WaterTankManager *manager,
                               CentralManagerData *central,
                               ControlPanelManager *controlPanel);

#endif // TEST_PIPES_H
