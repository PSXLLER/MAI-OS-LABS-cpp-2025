#ifdef _WIN32
#include "os_wrapper.h"
#include <windows.h>
#include <process.h>
#include <cstdlib>

struct os_thread {
    HANDLE h;
};

unsigned __stdcall thread_start(void* pack) {
    os_thread_func fn = ((os_thread_func*)pack)[0];
    void* arg         = ((void**)pack)[1];
    free(pack);
    fn(arg);
    return 0;
}

os_thread* os_thread_create(os_thread_func fn, void* arg) {
    void** pack = (void**)malloc(sizeof(void*) * 2);
    pack[0] = (void*)fn;
    pack[1] = arg;

    os_thread* t = new os_thread;
    t->h = (HANDLE)_beginthreadex(NULL, 0, thread_start, pack, 0, NULL);
    return t;
}

void os_thread_join(os_thread* t) {
    WaitForSingleObject(t->h, INFINITE);
}

void os_thread_destroy(os_thread* t) {
    CloseHandle(t->h);
    delete t;
}

struct os_semaphore {
    HANDLE h;
};

os_semaphore* os_semaphore_create(int initial) {
    os_semaphore* s = new os_semaphore;
    s->h = CreateSemaphoreA(NULL, initial, 1000000, NULL);
    return s;
}

void os_semaphore_wait(os_semaphore* s) {
    WaitForSingleObject(s->h, INFINITE);
}

void os_semaphore_signal(os_semaphore* s) {
    ReleaseSemaphore(s->h, 1, NULL);
}

void os_semaphore_destroy(os_semaphore* s) {
    CloseHandle(s->h);
    delete s;
}

#endif
