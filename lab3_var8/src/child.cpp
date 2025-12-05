#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "shared.h"
#include "os_wrapper.h"

int main() 
{
    SharedRegion* reg =
        (SharedRegion*)os_map_shared_file(sizeof(SharedRegion));

    while (true) 
    {
        os_wait_ready();

        if (reg->buffer[0] == '\0') 
        {
            os_signal_child();
            break;
        }

        char* p = reg->buffer;
        char* end;

        long result = strtol(p, &end, 10);
        p = end;

        reg->error = 0;

        while (*p != '\0') 
        {
            long op = strtol(p, &end, 10);
            p = end;

            if (op == 0) 
            {
                reg->error = 1;
                break;
            }

            result /= op;
        }

        if (!reg->error)
            printf("%ld\n", result);

        os_signal_child();

        if (reg->error)
            break;
    }

    return 0;
}
