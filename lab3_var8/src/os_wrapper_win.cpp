#include "os_wrapper.h"
#include <windows.h>
#include <cstdio>

static HANDLE hMap = NULL;
static LPVOID mapped = NULL;

static HANDLE sem_parent = NULL;
static HANDLE sem_child  = NULL;

void os_cleanup_before_start() 
{
 // Windows сама удаляет
}

void* os_map_shared_file(size_t size) 
{

    hMap = CreateFileMappingA( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, (DWORD)size, "lab3_shm");

    mapped = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, size);

    sem_parent = CreateSemaphoreA(NULL, 0, 1, "lab3_sem_parent");
    sem_child  = CreateSemaphoreA(NULL, 0, 1, "lab3_sem_child");

    return mapped;
}

void os_wait_ready()  { WaitForSingleObject(sem_parent, INFINITE); }
void os_signal_ready(){ ReleaseSemaphore(sem_parent, 1, NULL);     }

void os_wait_child()  { WaitForSingleObject(sem_child, INFINITE); }
void os_signal_child(){ ReleaseSemaphore(sem_child, 1, NULL);      }

int os_create_child(const char* path, char* const argv[]) 
{

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    BOOL ok = CreateProcessA(NULL, (LPSTR)path, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

    if (!ok) 
    {
        printf("CreateProcess error: %lu\n", GetLastError());
        return 0;
    }

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 1;
}

void os_cleanup() 
{
    UnmapViewOfFile(mapped);
    CloseHandle(hMap);
}
