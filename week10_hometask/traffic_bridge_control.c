#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARS 12   
sem_t bridge;          
pthread_mutex_t print_lock;
void* car(void* arg) {
    int id = *(int*)arg;
    int time_needed = (rand() % 4) + 1; // 1–4 seconds
    pthread_mutex_lock(&print_lock);
    printf("Car %d arrived at the bridge.\n", id);
    pthread_mutex_unlock(&print_lock);
    sem_wait(&bridge); 
    pthread_mutex_lock(&print_lock);
    printf("Car %d ENTERED the bridge (will take %d sec).\n", id, time_needed);
    pthread_mutex_unlock(&print_lock);
    sleep(time_needed);
    pthread_mutex_lock(&print_lock);
    printf("Car %d LEFT the bridge.\n", id);
    pthread_mutex_unlock(&print_lock);
    sem_post(&bridge); 
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t cars[NUM_CARS];
    int ids[NUM_CARS];

    sem_init(&bridge, 0, 3);             
    pthread_mutex_init(&print_lock, NULL);

    for (int i = 0; i < NUM_CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &ids[i]);

        usleep(200000); 
    }

    for (int i = 0; i < NUM_CARS; i++) {
        pthread_join(cars[i], NULL);
    }
    sem_destroy(&bridge);
    pthread_mutex_destroy(&print_lock);
    return 0;
}
