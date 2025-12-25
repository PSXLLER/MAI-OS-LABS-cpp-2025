#pragma once

struct SharedRegion 
{
    int ready;
    int error;
    char buffer[1024];
};
