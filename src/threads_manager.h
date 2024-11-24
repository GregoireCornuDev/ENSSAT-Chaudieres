#ifndef THREADS_MANAGER_H
#define THREADS_MANAGER_H

#include <pthread.h>
#include <stddef.h>

typedef struct {
    pthread_t* threads;                     // Tableau dynamique des threads
    void** start_routines;                  // Tableau dynamique des pointeurs de fonctions
    void** args;                            // Arguments pour les threads
    size_t count;                           // Nombre actuel de threads dans la liste
    size_t capacity;                        // Capacité maximale actuelle du tableau
} ThreadList;


// Initialiser la liste des threads
void thread_list_init(ThreadList* list, size_t initial_capacity);

// Ajouter un thread avec sa fonction de démarrage et ses arguments
void thread_list_add(ThreadList* list, void* (*start_routine)(void*), void* arg);

// Démarrer un seul thread
int start_thread(pthread_t* thread, void* (*start_routine)(void*), void* arg);

// Démarrer tous les threads de la liste
void thread_list_start_all(ThreadList* list);

// Attendre que tous les threads de la liste se terminent
void thread_list_join_all(ThreadList* list);

// Nettoyer et libérer la mémoire associée à la liste des threads
void thread_list_destroy(ThreadList* list);

int start_thread_adv(pthread_t* thread, void* (*start_routine)(void*), void* arg);

#endif // THREADS_MANAGER_H
