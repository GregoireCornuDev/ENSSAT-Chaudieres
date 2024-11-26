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
    for (size_t i = 0; i < list->count; ++i) {
        printf("starting thread %lu\n", i);
/*
        printf("routine du thread %ld : %p\n", i, list->start_routines[i]);
        printf("argument du thread %ld :  %p\n", i, list->args[i]);
*/

        //sleep(1);
        if (start_thread(&list->threads[i], (void* (*)(void*))list->start_routines[i], list->args[i]) != 0) {
            perror("Erreur lors de la création du thread");
        }
        printf("started thread %lu\n", i);
    }
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
