#ifndef CONTROL_PANEL_MANAGER_H
#define CONTROL_PANEL_MANAGER_H

// Définition de la structure WaterTankManager
typedef struct {
    int water_average_pipe[2]; // Pipe pour le niveau moyen transmis par le central
    int water_average_gui_pipe[2]; // Pipe pour envoyer le niveau moyen à l'interface graphique
    float water_average;
    int fuel_average_pipe[2]; // Pipe pour le niveau moyen transmis par le central
    int fuel_average_gui_pipe[2]; // Pipe pour envoyer le niveau moyen à l'interface graphique
    float fuel_average;
} ControlPanelManager;

// Fonction principale du thread
void *control_panel_manager_thread(void *arg);

// Initialise le ControlPanelManager
ControlPanelManager *control_panel_manager_init();

#endif //CONTROL_PANEL_MANAGER_H
