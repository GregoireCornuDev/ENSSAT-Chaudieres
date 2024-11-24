#include <control_panel_gui.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <unistd.h> // Gestion des pipes
#include "water_tank/water_tank_manager.h"
#include "fuel_tank/fuel_tank_manager.h"
#include "threads_manager.h"
#include "pipes_manager.h"
#include "tests/tests_pipes.h"


int main()
{
    printf("Let's go !\n");

    // Déclarations des structures
    WaterTankSimulator waterSimulation;
    WaterTankManager waterManager;
    CentralManagerData centralManager;
    ControlPanelManager controlPanelManager;

    // Initialisation de CentralManagerData avant de l'utiliser
    centralManager.water_level = 0.0;
    centralManager.water_average = 0.0;
    centralManager.fuel_level = 0.0;
    centralManager.fuel_average = 0.0;


    // Démarrer tous les pipes
    setup_water_pipes(&waterSimulation, &waterManager, &centralManager, &controlPanelManager);

    ThreadList thread_list;
    thread_list_init(&thread_list, 10);

    // Ajouter des threads
    thread_list_add(&thread_list, water_tank_simulation_thread, &waterSimulation);
    thread_list_add(&thread_list, water_tank_manager_thread, &waterManager);
    thread_list_add(&thread_list, control_panel_manager_thread, &controlPanelManager);
    thread_list_add(&thread_list, central_manager_thread, &centralManager);

    // Démarrer tous les threads
    thread_list_start_all(&thread_list);

    // Tests de DEBUG
    test_pipes_communication(&waterSimulation, &waterManager, &centralManager, &controlPanelManager);


    sleep(30);

    // Gestion de la fenêtre
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur SDL_image : %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Panneau de contrôle",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur fenêtre : %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }


    // Initialiser le panneau de contrôle
    ControlPanelGUI *panel = control_panel_gui_init(renderer);
    if (!panel) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Boucle principale
    int running = 1;
    SDL_Event event;
    char input;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);
        control_panel_gui_render(panel); // Afficher les images
        SDL_RenderPresent(renderer);

    }



    // Boucle de simulation simple pour envoyer des commandes aux réservoirs
    printf("Arrêt du programme...\n");

    // Attendre la fin de tous les threads
    thread_list_join_all(&thread_list);

    // Nettoyer les ressources
    thread_list_destroy(&thread_list);

    // Nettoyer les ressources
    control_panel_gui_destroy(panel);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}


