#ifndef _WIN32
#include "os_wrapper.h"
#include <pthread.h>
#include <semaphore.h>
#include <cstdlib>

struct os_thread {
    pthread_t t;
};

void* thread_start(void* pack) {
    os_thread_func fn = ((os_thread_func*)pack)[0];
    void* arg         = ((void**)pack)[1];
    free(pack);
    return fn(arg);
}

os_thread* os_thread_create(os_thread_func fn, void* arg) {
    void** pack = (void**)malloc(sizeof(void*) * 2);
    pack[0] = (void*)fn;
    pack[1] = arg;

    os_thread* t = new os_thread;
    pthread_create(&t->t, NULL, thread_start, pack);
    return t;
}

void os_thread_join(os_thread* t) {
    pthread_join(t->t, NULL);
}

void os_thread_destroy(os_thread* t) {
    delete t;
}

struct os_semaphore {
    sem_t sem;
};

os_semaphore* os_semaphore_create(int initial) {
    os_semaphore* s = new os_semaphore;
    sem_init(&s->sem, 0, initial);
    return s;
}

void os_semaphore_wait(os_semaphore* s) {
    sem_wait(&s->sem);
}

void os_semaphore_signal(os_semaphore* s) {
    sem_post(&s->sem);
}

void os_semaphore_destroy(os_semaphore* s) {
    sem_destroy(&s->sem);
    delete s;
}

#endif
