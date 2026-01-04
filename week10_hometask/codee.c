#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t slots;

void* vehicle(void* arg) {
    int num = *(int*)arg;

    printf("Vehicle %d wants to enter.\n", num);

    sem_wait(&slots);

    printf("Vehicle %d entered successfully.\n", num);

    sleep(2);

    printf("Vehicle %d exited.\n", num);

    sem_post(&slots);

    return NULL;
}

int main() {
    pthread_t threads[10];
    int numbers[10];

    sem_init(&slots, 0, 3);

    for (int i = 0; i < 10; i++) {
        numbers[i] = i + 1;
        pthread_create(&threads[i], NULL, vehicle, &numbers[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&slots);
    return 0;
}
