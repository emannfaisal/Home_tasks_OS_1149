 #include <stdio.h>
 #include <pthread.h>
 int counter = 0; 
 void* increment(void* arg) {
 for (int i = 0; i < 100000; i++) {   //no synchronization so inconsistent results will be there
   counter++; 
 }
 return NULL;
 }
 int main() {
      pthread_t threadd[3];
      for(int i=0;i<3;i++){
        pthread_create(&threadd[i], NULL, increment, NULL);
      }
      for(int i=0;i<3;i++){
        pthread_join(threadd[i], NULL);
      }
      printf("value:%d\n",counter);
 return 0;
 }