#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    int n;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    printf("\"");
    return obj;
}

enum {
    IDLE = 0,
    NUM = 1,
};

int flag = IDLE;
int cur_char = 0;
pthread_mutex_t zero_mutex = PTHREAD_MUTEX_INITIALIZER;

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.

void zero(ZeroEvenOdd* obj) {
    while(1)
    {
        if (cur_char == obj->n)
            return;

        pthread_mutex_lock(&zero_mutex);
        if (flag == IDLE){
            printf("0");
            cur_char++;
            flag = NUM;
        }
        pthread_mutex_unlock(&zero_mutex);
    }
}

void even(ZeroEvenOdd* obj) {
    while(1)
    {
        if (cur_char == obj->n)
            return;

        pthread_mutex_lock(&zero_mutex);
        if (flag == NUM && (cur_char % 2) == 0) {
            flag = IDLE;
            printf("%d", cur_char);
        }
        pthread_mutex_unlock(&zero_mutex);
    }
}

void odd(ZeroEvenOdd* obj) {
    while(1)
    {
        if (cur_char == obj->n)
            return;

        pthread_mutex_lock(&zero_mutex);
        if (flag == NUM && (cur_char % 2) == 1) {
            flag = IDLE;
            printf("%d", cur_char);
        }
        pthread_mutex_unlock(&zero_mutex);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    printf("\"");
    free(obj);
}

void test_zero_even_odd()
{
    pthread_t p_zero, p_odd, p_even;
    ZeroEvenOdd *obj = zeroEvenOddCreate(100);

    pthread_create(&p_zero, NULL, zero, obj);
    pthread_create(&p_even, NULL, even, obj);
    pthread_create(&p_odd, NULL, odd, obj);

    pthread_join(p_zero, NULL);
    pthread_join(p_even, NULL);
    pthread_join(p_odd, NULL);
    zeroEvenOddFree(obj);
}