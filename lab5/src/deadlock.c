#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;

void deadlock1(void* arg) {
    pthread_mutex_lock(&mut1);
    for (int i = 0; i < 50000; i++);
    printf("lock 1 \n");
    pthread_mutex_lock(&mut2);


    pthread_mutex_unlock(&mut1);
    pthread_mutex_unlock(&mut2);
}

void deadlock2(void* arg) {
    pthread_mutex_lock(&mut2);
    for (int i = 0; i < 50000; i++);
    printf("lock 2 \n");
    pthread_mutex_lock(&mut1);


    pthread_mutex_unlock(&mut2);
    pthread_mutex_unlock(&mut1);
}

int main(int argc, char **argv) {
    pthread_t th1, th2;

    pthread_create(&th1, NULL, (void*)deadlock1, NULL);
    pthread_create(&th2, NULL, (void*)deadlock2, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0;
}