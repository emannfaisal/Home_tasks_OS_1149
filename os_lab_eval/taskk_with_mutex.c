 #include <stdio.h>
 #include <pthread.h>
 int counter = 0;
 pthread_mutex_t mutexxx;  //mutex is needed so that one thread accesses this
 // critical section at a time and the synchronization can be mantained.
 void* incrementtt(void* arg) {
    pthread_mutex_lock(&mutexxx);
    for (int i = 0; i < 100000; i++) {
        counter++;
    }
    pthread_mutex_unlock(&mutexxx);
    return NULL;
 }
 int main() {
    pthread_mutex_init(&mutexxx,NULL);
      pthread_t threadd[3];
      for(int i=0;i<3;i++){
        pthread_create(&threadd[i], NULL, incrementtt, NULL);
      }
      for(int i=0;i<3;i++){
        pthread_join(threadd[i], NULL);
      }
     printf("value:%d \n",counter);
     pthread_mutex_destroy(&mutexxx);
     return 0;
 }