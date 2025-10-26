#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void* worker_thread(void* arg) {
    int thread_num = *(int*)arg;
    pthread_t tid = pthread_self(); 

    int sleep_time = rand() % 3 + 1;

    printf("Thread %d (ID: %lu): Starting work... Sleeping for %d seconds\n",
           thread_num, tid, sleep_time);

    sleep(sleep_time);

    printf("Thread %d (ID: %lu): Work completed!\n", thread_num, tid);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_args[5];
    srand(time(NULL)); 

    // Create 5 threads
    for (int i = 0; i < 5; i++) {
        thread_args[i] = i + 1;
        printf("Main: Creating thread %d\n", i + 1);
        pthread_create(&threads[i], NULL, worker_thread, &thread_args[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
        printf("Main: Thread %d has finished\n", i + 1);
    }

    printf("All threads completed!\n");
    return 0;
}
