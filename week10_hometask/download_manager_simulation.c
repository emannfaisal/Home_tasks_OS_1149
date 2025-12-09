#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

sem_t slots;   

void* downloadFile(void* arg) {
    int id = *(int*)arg;
    int time_needed = rand() % 5 + 1; 
    sem_wait(&slots);

    printf("Download %d started (will take %d seconds)\n", id, time_needed);
    sleep(time_needed);

    printf("Download %d finished!!\n", id);
    sem_post(&slots);  
    return NULL;
}

int main() {
    srand(time(NULL));

    sem_init(&slots, 0, 3); // Only 3 downloads at a time

    pthread_t threads[8];
    int ids[8];

    for (int i = 0; i < 8; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, downloadFile, &ids[i]);
    }
    for (int i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&slots);
    return 0;
}
