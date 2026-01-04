#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int student_id;
    char name[50];
    float gpa;

} Student;
void* check_and_print(void* arg) {
    Student* s =(Student*)arg; 
    printf("Student ID: %d\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("GPA: %.2f\n", s->gpa);
    int* eligible = malloc(sizeof(int));
    if (s->gpa >= 3.5) {
        *eligible = 1;
    } else {
        *eligible = 0;
    }
    return ((void*)eligible) ;
}

int main() {
    pthread_t threads[3];
    Student students[3]={
        {101, "Eman", 3.8},
        {102, "Ali", 3.2},
        {103, "Sara", 3.9}
    };

    int* eligibility[3];
    int dean_count =0;
    for (int i =0; i < 3; i++) {
        pthread_create(&threads[i], NULL, check_and_print, &students[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], (void**)&eligibility[i]);
        dean_count += *eligibility[i];
    }
    printf("\n-----------------------------------\n");
    printf("Total students on Dean's List: %d\n", dean_count);
    printf("Main thread: Work completed.\n");
    return 0;
}

