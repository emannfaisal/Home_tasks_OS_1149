 #include <stdio.h>
 #include <pthread.h>
 typedef struct {
 float id;
 char* message;
 } ThreadData;
 void* printData(void* arg) {
 ThreadData* data = (ThreadData*)arg;
 printf("CGPA: %f  Name: %s\n", data->id, data->message);
 return NULL;
 }
 int main() {
 pthread_t t1;
 ThreadData data1 = {3.71, "my name is EMAN FAISAL"};

 pthread_create(&t1, NULL, printData, &data1);
 pthread_join(t1, NULL);
 printf("All threads done.\n");
 return 0;
 }