#pragma once
#include <cstddef>

typedef void* (*os_thread_func)(void*);

struct os_thread;
struct os_semaphore;

os_thread* os_thread_create(os_thread_func fn, void* arg);
void       os_thread_join(os_thread* t);
void       os_thread_destroy(os_thread* t);

os_semaphore* os_semaphore_create(int initial);
void          os_semaphore_wait(os_semaphore* s);
void          os_semaphore_signal(os_semaphore* s);
void          os_semaphore_destroy(os_semaphore* s);
