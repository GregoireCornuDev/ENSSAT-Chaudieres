//
// Created by gregoire on 24/11/24.
//

#ifndef PIPES_MANAGER_H
#define PIPES_MANAGER_H


#include "control_panel_manager.h"
#include "water_tank_simulation.h"
#include "water_tank_manager.h"
#include "central_manager/central_manager.h"

int setup_water_pipes(WaterTankSimulator *simulation, WaterTankManager *manager, CentralManagerData *central_data, ControlPanelManager *controlPanel);



#endif //PIPES_MANAGER_H
