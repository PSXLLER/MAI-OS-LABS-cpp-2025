#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>
typedef HMODULE LibHandle;
#else
#include <dlfcn.h>
typedef void* LibHandle;
#endif

LibHandle os_load_library(const std::string& path);
void*     os_load_symbol (LibHandle lib, const std::string& name);
void      os_close_library(LibHandle lib);
