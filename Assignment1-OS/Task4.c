#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* compute_factorial(void* arg) {
    int n = *(int*)arg;  
    long long* result =malloc(sizeof(long long)); 

    *result = 1; 
    for (int i= 1;i<= n; i++) {
        *result *= i;
    }
    return (void*)result;
}

int main() {
    pthread_t thread;
    int num;
    void* factorial_result;

    printf("Enter integer: ");
    scanf("%d", &num);

    pthread_create(&thread, NULL,compute_factorial, &num);

    pthread_join(thread,&factorial_result);

    printf("Factorial of %d = %d\n",num, *(int*)factorial_result);
    free(factorial_result);

    printf("Main thread: Work completed.\n");
    return 0;
}
