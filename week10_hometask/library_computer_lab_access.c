#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define NUM_STUDENTS 10   // total students
sem_t computers;          // counting semaphore for available computers
pthread_mutex_t lock;     // mutex for shared array
int *computerUsedBy;      // array: computerUsedBy[i] = student ID OR -1
int K; // number of computers
void* student(void* arg) {
    int id = *(int*)arg;
    // wait for a computer to be free
    sem_wait(&computers);
    pthread_mutex_lock(&lock);
    int assigned = -1;

    // find a free computer in the shared array
    for (int i = 0; i < K; i++) {
        if (computerUsedBy[i] == -1) {
            computerUsedBy[i] = id;  // assign this computer
            assigned = i;
            printf("Student %d is using Computer %d\n", id, i);
            break;
        }
    }

    pthread_mutex_unlock(&lock);

    // student uses the computer for random time (1–4 sec)
    sleep(rand() % 4 + 1);

    // student leaves
    pthread_mutex_lock(&lock);
    computerUsedBy[assigned] = -1;
    printf("Student %d left Computer %d\n", id, assigned);
    pthread_mutex_unlock(&lock);

    // free one computer
    sem_post(&computers);

    return NULL;
}

int main() {
    srand(time(NULL));

    printf("Enter number of computers in lab: ");
    scanf("%d", &K);

    computerUsedBy = malloc(K * sizeof(int));

    // mark all computers as free
    for (int i = 0; i < K; i++) {
        computerUsedBy[i] = -1;
    }

    // initialize semaphore & mutex
    sem_init(&computers, 0, K);
    pthread_mutex_init(&lock, NULL);

    pthread_t threads[NUM_STUDENTS];
    int ids[NUM_STUDENTS];
    // create student threads
    for (int i = 0; i < NUM_STUDENTS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, student, &ids[i]);
    }
    // wait for all to finish
    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }
    // cleanup
    sem_destroy(&computers);
    pthread_mutex_destroy(&lock);
    free(computerUsedBy);

    return 0;
}
