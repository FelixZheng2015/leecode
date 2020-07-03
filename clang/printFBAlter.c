#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int n;
    pthread_mutex_t f_mutex, b_mutex;

    pthread_t pf;
    pthread_t pb;
} FooBar;

void printfoo()
{
    printf("foo");
}

void *foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->f_mutex);
        printfoo();
        pthread_mutex_unlock(&obj->b_mutex);
    }
    return NULL;
}

void printbar()
{
    printf("bar");
}

void *bar(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {

        pthread_mutex_lock(&obj->b_mutex);
        printbar();
        pthread_mutex_unlock(&obj->f_mutex);
    }
    return NULL;
}

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*)malloc(sizeof(FooBar));
    obj->n = n;
    pthread_mutex_init(&obj->f_mutex, NULL);
    pthread_mutex_init(&obj->b_mutex, NULL);
    pthread_mutex_lock(&obj->b_mutex);

    pthread_create(&obj->pf, NULL, foo, obj);
    pthread_create(&obj->pb, NULL, bar, obj);
    return obj;
}

void fooBarFree(FooBar* obj) {
    pthread_join(obj->pf, NULL);
    pthread_join(obj->pb, NULL);
    pthread_mutex_destroy(&obj->f_mutex);
    pthread_mutex_destroy(&obj->b_mutex);
    free(obj);
}

int main()
{
    FooBar *obj = fooBarCreate(4);
    fooBarFree(obj);
}