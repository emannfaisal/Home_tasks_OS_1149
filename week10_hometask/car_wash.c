#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define NUM_CARS 10   // total cars arriving
sem_t stations;       // semaphore for 2 wash stations
pthread_mutex_t qlock;
int queueLength = 0;  // cars waiting in queue
void* carWash(void* arg) {
    int id = *(int*)arg;
    // Car arrives → joins queue
    pthread_mutex_lock(&qlock);
    queueLength++;
    printf("Car %d arrived. Queue length: %d\n", id, queueLength);
    pthread_mutex_unlock(&qlock);

    // Wait for washing station
    sem_wait(&stations);

    // Car enters → leaves queue
    pthread_mutex_lock(&qlock);
    queueLength--;
    printf("Car %d is being washed. Queue length: %d\n", id, queueLength);
    pthread_mutex_unlock(&qlock);

    sleep(3); // washing takes 3 seconds

    printf("Car %d finished washing.\n", id);
    sem_post(&stations); 
    return NULL;
}
int main() {
    srand(time(NULL));
    pthread_t cars[NUM_CARS];
    int ids[NUM_CARS];
    sem_init(&stations, 0, 2);     // 2 washing stations
    pthread_mutex_init(&qlock, NULL);
    for (int i = 0; i < NUM_CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, carWash, &ids[i]);
        usleep(300000); // small delay so arrivals look realistic
    }
    // wait for all cars
    for (int i = 0; i < NUM_CARS; i++) {
        pthread_join(cars[i], NULL);
    }
    sem_destroy(&stations);
    pthread_mutex_destroy(&qlock);

    return 0;
}
