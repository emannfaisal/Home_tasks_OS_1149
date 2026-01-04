#include <stdio.h>
#include <pthread.h>

void* compute(void* arg) {
    int num = *(int*)arg;  
    printf("Thread:Number = %d\n",num);
    printf("Thread: Square = %d\n",num*num);
    printf("Thread:Cube   = %d\n", num*num*num);
    return NULL;
}
int main() {
    pthread_t thread;
    int number;
    scanf("%d", &number);
    pthread_create(&thread, NULL, compute, &number);
    pthread_join(thread, NULL);
    printf("Main thread: Work completed.\n");
    return 0;
}
