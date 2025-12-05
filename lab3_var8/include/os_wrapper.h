#pragma once
#include <stddef.h>

void  os_cleanup_before_start();
void* os_map_shared_file(size_t size);

void  os_wait_ready();
void  os_signal_ready();

void  os_wait_child();
void  os_signal_child();

int   os_create_child(const char* path, char* const argv[]);
void  os_cleanup();
