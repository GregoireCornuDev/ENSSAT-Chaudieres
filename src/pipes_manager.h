//
// Created by gregoire on 24/11/24.
//

#ifndef PIPES_MANAGER_H
#define PIPES_MANAGER_H


#include "control_panel/control_panel_manager.h"
#include "control_panel/gui.h"
#include "simulation/water_tank_simulation.h"
#include "water_tank_manager.h"
#include "central_manager/central_manager.h"
#include "fuel_tank/fuel_tank_manager.h"
#include "simulation/fuel_tank_simulation.h"
#include "simulation/water_tank_simulation.h"

int setup_water_pipes(WaterTankSimulation *simulation, WaterTankManager *water_manager, CentralManager *central_manager, ControlPanelManager *control_manager, ControlPanelGUI *gui);

int setup_fuel_pipes(FuelTankSimulation *simulation, FuelTankManager *fuel_manager, CentralManager *central_manager, ControlPanelManager *control_manager, ControlPanelGUI *gui);


#endif //PIPES_MANAGER_H
