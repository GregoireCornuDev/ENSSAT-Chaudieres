#include "tank_simulation.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <asm-generic/errno-base.h>
#include <fcntl.h>    // Pour fcntl() et les constantes comme F_SETFL, O_NONBLOCK
#include "../config.h"
#include "../mutex_manager.h"



// Initialise le réservoir
void tank_simulation_init(TankSimulation *tank_simulation, char *content, float content_level) {

    tank_simulation->content = content;
    tank_simulation->content_level = content_level;
    tank_simulation->content_supply_valve = 0;
    tank_simulation->content_use_valve = 0.0f;
    tank_simulation->last_trigger = '0';

    printf("Simulation Tank %c : Initialisation OK \n", *content);


}

// Transmet le niveau de contenu
void content_level_transmit(TankSimulation *tank_simulation) {

    float content_level = tank_simulation->content_level;

    // Envoie au manager le niveau d'eau via le pipe
    //pthread_mutex_lock(&content_level_sensor_mutex);

    if (write(tank_simulation->content_level_sensor_pipe[1], &content_level, sizeof(content_level)) == -1) {
        perror("Erreur d'écriture dans simulation->content_level_sensor_pipe \n");
    }
    //pthread_mutex_unlock(&content_level_sensor_mutex);
}


// Informe du déclenchement d'un des capteurs
void content_level_sensors_trigger(TankSimulation *tank_simulation) {

    // Récupère le niveau de contenu depuis la struct
    float content_level = tank_simulation->content_level;
    char last_trigger = tank_simulation->last_trigger;
    char *content = tank_simulation->content;

    // Définit un trigger à partir de la mesure du niveau de content
    char new_trigger = content_level_measure(content_level);

    // Si le nouveau trigger est différent
    if (new_trigger != last_trigger) {
        printf("Simulation %s : Sensors trigger -> nouveau trigger à envoyer : %c \n", content,  new_trigger);

        // Enregistre le dernier trigger effectué dans la struct
        tank_simulation->last_trigger = new_trigger;

        // Transmet l'information au Fuel Tank Manager via le pipe
        if(write(tank_simulation->content_level_trigger_pipe[1], &new_trigger, sizeof(new_trigger)) == -1) {
            perror("Erreur d'écriture dans simulation->content_level_trigger_pipe \n");
        }
        printf("Simulation Fuel : Sensors trigger -> trigger envoyé : %c \n", new_trigger);

    }
}

// Analyse le niveau de contenu
char content_level_measure(float content_level) {

    char new_trigger = '0';

    // Analyse le niveau de contenu (Haute, Basse ou (très) basse)
    if (content_level < 10.0f) {
        new_trigger = 'b'; // Niveau très bas
    } else if (content_level < 30.0f) {
        new_trigger = 'B'; // Niveau bas
    } else if (content_level > 80.0f) {
        new_trigger = 'H'; // Niveau haut
    }
    // Si le niveau de contenu est > 30.0 et < 80.0, new_trigger conserve 'x'

    printf("Simulation : Sensors trigger -> trigger mesuré : %c \n", new_trigger);

    // Retourne le trigger
    return new_trigger;
}

// S'informe sur l'état de la vanne d'approvisionnement
void supply_valve_open_close(TankSimulation *tank_simulation) {

    int open_close_valve = 0;// open = 1 | close = 0

    char *content = tank_simulation->content;
    printf("Simulation %s : Vanne d'approvisionnement -> ? \n", content);

    // Paramètre le pipe comme non bloquant
    int flags = fcntl(tank_simulation->content_supply_pipe[0], F_GETFL, 0);
    fcntl(tank_simulation->content_supply_pipe[0], F_SETFL, flags | O_NONBLOCK);

    // Reçoit l'ordre d'ouvrir ou fermer la vanne d'approvisionnement s'il est présent dans le pipe
    if(read(tank_simulation->content_supply_pipe[0], &open_close_valve, sizeof(open_close_valve)) > 0) {

        printf("Simulation %s : Vanne d'approvisionnement -> commande reçue : %d \n", content, open_close_valve);
        tank_simulation->content_supply_valve = open_close_valve;

    // ... sinon, continue sans rien faire
    } else {
        if (errno == EAGAIN) {
            //printf("Simulation %c : Vanne d'approvisionnement -> pipe content_supply_pipe vide \n", *content);
        } else {
            perror("Erreur de lecture dans simulation->content_supply_pipe \n");
        }
        //printf("Simulation Fuel : Vanne d'approvisionnement -> Pas d'action \n");
    }
}

// S'informe sur l'état d'ouverture proportionnel de la vanne d'usage
void usage_valve_control(TankSimulation *tank_simulation) {

    float content_use_valve = 0.5f;

    tank_simulation->content_use_valve = content_use_valve;

}

// Met à jour le niveau de content dans le réservoir en fonction de l'ouverture des vannes
void content_level_update(TankSimulation *tank_simulation) {

    float content_level = tank_simulation->content_level;
    char *content = tank_simulation->content;

    // Approvisionnement ouvert/fermé
    if (tank_simulation->content_supply_valve == 0) {

        printf("Simulation %s : Approvisionnement eau -> fermé \n", content);

    } else if (tank_simulation->content_supply_valve == 1) {

        printf("Simulation %s : Approvisionnement eau -> ouvert \n", content);
        content_level += WATER_FLOW_RATE;

    } else {
        printf("Simulation %s : ", content);
        perror("Approvisionnement -> Commande inmpossible");

    }

    // Usage proportionnel
    content_level -= tank_simulation->content_use_valve;


    // Met à jour le niveau dd contenu dans la structure
    tank_simulation->content_level = content_level;
}


