#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define BUF_SIZE 3 /* size of shared buffer */

int buffer[BUF_SIZE]; /* shared buffer */
int add = 0;
int rem = 0;
int num = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_reader = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_writer = PTHREAD_COND_INITIALIZER;

void *writer (void *param);
void *reader (void *param);

int main(void)
{
    pthread_t tid1, tid2;

    if(pthread_create(&tid1, NULL, writer, NULL) != 0) {
        fprintf("stderr, Unable to create writer thread");
        exit(1);
    }

    if(pthread_create(&tid2, NULL, reader, NULL) != 0) {
        fprintf("stderr, Unable to create reader thread");
        exit(1);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}

void *writer(void *param)
{

}

void *reader(void *param)
{

}
