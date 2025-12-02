#include "os_wrapper.h"
#include "shared.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

static sem_t* sem_parent = NULL;
static sem_t* sem_child  = NULL;
static void* mapped = NULL;

void os_cleanup_before_start() 
{
    sem_unlink("/lab3_sem_parent");
    sem_unlink("/lab3_sem_child");
    shm_unlink("/lab3_shm");
}

void* os_map_shared_file(size_t size) 
{
    int fd = shm_open("/lab3_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, size);

    mapped = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_parent = sem_open("/lab3_sem_parent", O_CREAT, 0666, 0);
    sem_child  = sem_open("/lab3_sem_child",  O_CREAT, 0666, 0);

    return mapped;
}

void os_wait_ready()  { sem_wait(sem_parent); }
void os_signal_ready(){ sem_post(sem_parent); }

void os_wait_child()  { sem_wait(sem_child); }
void os_signal_child(){ sem_post(sem_child); }

int os_create_child(const char* path, char* const argv[]) 
{
    pid_t pid = fork();
    if (pid == 0) {
        execv(path, argv);
        perror("execv");
        _exit(1);
    }
    return 1;
}

void os_cleanup() 
{
    munmap(mapped, sizeof(SharedRegion));
}
