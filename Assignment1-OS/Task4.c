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
    return result;
}

int main() {
    pthread_t thread;
    int num;
    long long* factorial_result;

    printf("Enter integer: ");
    scanf("%d", &num);

    pthread_create(&thread, NULL,compute_factorial, &num);

    pthread_join(thread, (void**)&factorial_result);

    printf("Factorial of %d = %lld\n",num, *factorial_result);
    free(factorial_result);

    printf("Main thread: Work completed.\n");
    return 0;
}
