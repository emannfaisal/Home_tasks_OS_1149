#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define NUM_WORKERS 3
#define NUM_TASKS 10
sem_t worker_sem;          
pthread_mutex_t task_lock; 

int currentTask = 1;        

void* worker(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&worker_sem);  
        pthread_mutex_lock(&task_lock);
        if (currentTask > NUM_TASKS) {
            pthread_mutex_unlock(&task_lock);
            sem_post(&worker_sem);  
            break;
        }
        int taskID = currentTask;
        currentTask++;
        pthread_mutex_unlock(&task_lock);
        int time_needed = rand() % 2 + 1;
        printf("Worker %d started Task %d (time %d sec)\n",
               id, taskID, time_needed);

        sleep(time_needed);
        printf("Worker %d finished Task %d\n", id, taskID);
    }
    return NULL;
}
int main() {
    srand(time(NULL));
    pthread_t workers[NUM_WORKERS];
    int ids[NUM_WORKERS];
    sem_init(&worker_sem, 0, 0);
    pthread_mutex_init(&task_lock, NULL);
    for (int i = 0; i < NUM_WORKERS; i++) {
        ids[i] = i + 1;
        pthread_create(&workers[i], NULL, worker, &ids[i]);
    }
    for (int i = 1; i <= NUM_TASKS; i++) {
        printf("Task %d arrived\n", i);
        sem_post(&worker_sem); 
        usleep(100000);        
    }
    for (int i = 0; i < NUM_WORKERS; i++) {
        sem_post(&worker_sem);
    }
    for (int i = 0; i < NUM_WORKERS; i++) {
        pthread_join(workers[i], NULL);
    }
    sem_destroy(&worker_sem);
    pthread_mutex_destroy(&task_lock);
    return 0;
}
