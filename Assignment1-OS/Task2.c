#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg){
    char* thread_name=(char*) arg;
    printf("Hello %s! Welcome to the world of THreads \n",thread_name);
    return NULL;
}


int main(){
pthread_t threadd;
char* name="eman";
pthread_create(&threadd,NULL,thread_func,name);
printf("Main thread:Waiting for greeting...\n");
pthread_join(threadd,NULL);
printf("Greeting completed\n");
return 0;
}