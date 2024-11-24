//
// Created by gregoire on 24/11/24.
//

#ifndef CONTROL_PANEL_MANAGER_H
#define CONTROL_PANEL_MANAGER_H
#include <control_panel_gui.h>

// Définition de la structure WaterTankManager
typedef struct {
    int water_average_pipe[2]; // Pipe pour le niveau moyen transmis par le central
    ControlPanelGUI* gui;        // Référence au GUI
} ControlPanelManager;

// Fonction principale du thread
void* control_panel_manager_thread(void* arg);

// Met à jour le GUI
void update_gui(ControlPanelGUI* gui, ControlPanelData* data);

#endif //CONTROL_PANEL_MANAGER_H
