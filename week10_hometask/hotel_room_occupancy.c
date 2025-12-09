#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
sem_t rooms;           
int occupied = 0;      
pthread_mutex_t lock;  
void* rooms_place(void* arg) {
    int id = *(int*)arg;
    // Wait for a free room
    sem_wait(&rooms);
    pthread_mutex_lock(&lock);
    occupied++;
    printf("Person %d entered | Rooms occupied: %d\n", id, occupied);
    pthread_mutex_unlock(&lock);
    sleep(rand() % 3 + 1);
    pthread_mutex_lock(&lock);
    occupied--;
    printf("Person %d left    | Rooms occupied: %d\n", id, occupied);
    pthread_mutex_unlock(&lock);

    sem_post(&rooms);
    return NULL;
}
int main() {
    int N_ROOMS, N_PEOPLE;
    srand(time(NULL));
    printf("Enter number of rooms: ");
    scanf("%d", &N_ROOMS);
    printf("Enter number of people: ");
    scanf("%d", &N_PEOPLE);
    pthread_t t[N_PEOPLE];
    int ids[N_PEOPLE];
    // Initialize semaphore with user-defined rooms
    sem_init(&rooms, 0, N_ROOMS);
    pthread_mutex_init(&lock, NULL);
    // Create threads for each person
    for (int i = 0; i < N_PEOPLE; i++) {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, rooms_place, &ids[i]);
    }
    // Wait for all threads to finish
    for (int i = 0; i < N_PEOPLE; i++) {
        pthread_join(t[i], NULL);
    }
    sem_destroy(&rooms);
    pthread_mutex_destroy(&lock);
    return 0;
}
