#include "threads_manager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Initialiser la liste des threads
void thread_list_init(ThreadList* list, size_t initial_capacity) {
    list->threads = malloc(initial_capacity * sizeof(pthread_t));
    list->start_routines = malloc(initial_capacity * sizeof(void*));
    list->args = malloc(initial_capacity * sizeof(void*));
    list->count = 0;
    list->capacity = initial_capacity;
}

// Ajouter un thread avec sa fonction de démarrage et ses arguments
void thread_list_add(ThreadList* list, void* (*start_routine)(void*), void* arg) {
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        list->threads = realloc(list->threads, new_capacity * sizeof(pthread_t));
        list->start_routines = realloc(list->start_routines, new_capacity * sizeof(void*));
        list->args = realloc(list->args, new_capacity * sizeof(void*));
        list->capacity = new_capacity;
    }

    list->start_routines[list->count] = (void*)start_routine; // Stocker comme un void*
    list->args[list->count] = arg;
    list->count++;
}

// Démarrer un thread
int start_thread(pthread_t* thread, void* (*start_routine)(void*), void* arg) {
    return pthread_create(thread, NULL, start_routine, arg);
}

// Démarrer tous les threads de la liste
void thread_list_start_all(ThreadList* list) {
    for (size_t i = 0; i <= list->count; ++i) {
        printf("starting thread %lu\n", i);
        sleep(2);

        // Exemple d'appel de start_thread dans ton code
        if (start_thread_adv(&list->threads[i], (void* (*)(void*))list->start_routines[i], list->args[i]) != 0) {
            perror("Erreur lors de la création du thread");
        } else {
            printf("Thread %ld créé avec succès.\n", i);
        }

        if (start_thread(&list->threads[i], (void* (*)(void*))list->start_routines[i], list->args[i]) != 0) {
            perror("Erreur lors de la création du thread");
        }
        printf("started thread %lu\n", i);
    }
}

// Fonction améliorée pour démarrer le thread avec une vérification
int start_thread_adv(pthread_t* thread, void* (*start_routine)(void*), void* arg) {
    // Vérification de la validité des arguments
    if (thread == NULL) {
        fprintf(stderr, "Erreur : thread est NULL\n");
        return -1;
    }
    if (start_routine == NULL) {
        fprintf(stderr, "Erreur : start_routine est NULL\n");
        return -1;
    }
    if (arg == NULL) {
        fprintf(stderr, "Erreur : arg est NULL\n");
    }

    // Tentative de création du thread
    int ret = pthread_create(thread, NULL, start_routine, arg);
    if (ret != 0) {
        // Si l'appel échoue, afficher le code d'erreur
        fprintf(stderr, "Erreur lors de la création du thread : %s\n", strerror(ret));
        return ret;  // Retourne l'erreur pour un traitement ultérieur
    }

    printf("Thread créé avec succès. ID: %lu\n", (unsigned long)*thread);
    return 0;  // Succès
}

// Attendre que tous les threads de la liste se terminent
void thread_list_join_all(ThreadList* list) {
    for (size_t i = 0; i < list->count; ++i) {
        pthread_join(list->threads[i], NULL);
    }
}

// Nettoyer et libérer la mémoire associée à la liste des threads
void thread_list_destroy(ThreadList* list) {
    free(list->threads);
    free(list->start_routines);
    free(list->args);
}
