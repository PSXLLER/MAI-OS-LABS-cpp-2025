#include "os_wrapper.h"
#include <iostream>

LibHandle os_load_library(const std::string& path) 
{
#ifdef _WIN32
    return LoadLibraryA(path.c_str());
#else
    return dlopen(path.c_str(), RTLD_LAZY);
#endif
}

void* os_load_symbol(LibHandle lib, const std::string& name) 
{
#ifdef _WIN32
    return reinterpret_cast<void*>(GetProcAddress(lib, name.c_str()));
#else
    return dlsym(lib, name.c_str());
#endif
}

void os_close_library(LibHandle lib) 
{
#ifdef _WIN32
    FreeLibrary(lib);
#else
    dlclose(lib);
#endif
}
