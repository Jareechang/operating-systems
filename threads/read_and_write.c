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

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;
    int i;

    if(pthread_create(&tid1, NULL, writer, NULL) != 0) {
        fprintf(stderr,"Unable to create writer thread\n");
        exit(1);
    }

    if(pthread_create(&tid2, NULL, reader, NULL) != 0) {
        fprintf(stderr, "Unable to create reader thread\n");
        exit(1);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}

void *writer(void *param)
{
    int i;

    for(i = 0; i <= 20; i++) {
        pthread_mutex_lock(&m); /* lock the thread */
        if(num > BUF_SIZE) {
            exit(1); /* overflow */
        }
        while(num == BUF_SIZE) { /* block if buffer is full */
            pthread_cond_wait(&c_writer, &m);
        }

        buffer[add] = i;
        add = (add + 1) % BUF_SIZE; /* mod (add) to ensure within range - circular  */
        num++;
        pthread_mutex_unlock(&m); /* unlock thread */
        pthread_cond_signal(&c_reader); /* sends signal to reader, if it is waiting */
        /* -- FOR DEBUG */ 
        printf("writer: wrote to buffer = %d\n", i);
        fflush(stdout);
    }
    return 0;
}

void *reader(void *param)
{
    int i;

    while(1) {
        pthread_mutex_lock(&m); /* lock the thread */
        if(num < 0) {
            exit(1);
        }

        while(num == 0) { /* block if buffer empty */
            pthread_cond_wait(&c_reader, &m);
        }

        i = buffer[rem];
        rem = (rem + 1) % BUF_SIZE;
        num--;

        pthread_mutex_unlock(&m);
        pthread_cond_signal(&c_writer);

        if(i == 20) {
            pthread_exit(EXIT_SUCCESS);
        }
        /* -- FOR DEBUG */ 
        printf("read: read from buffer = %d\n", i);
        fflush(stdout);
    }
    return 0;
}
