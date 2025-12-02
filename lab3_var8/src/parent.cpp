#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "shared.h"
#include "os_wrapper.h"

int main(int argc, char** argv) 
{

    if (argc < 2) {
        fprintf(stderr, "usage: %s input.txt\n", argv[0]);
        return 1;
    }

    os_cleanup_before_start();

    SharedRegion* reg = (SharedRegion*)os_map_shared_file(sizeof(SharedRegion));

    memset(reg, 0, sizeof(SharedRegion));

    char* child_argv[] = { (char*)"child", NULL };
    os_create_child(child_argv[0], child_argv);

    FILE* f = fopen(argv[1], "r");
    if (!f) 
    {
        perror("open");
        return 1;
    }

    char line[1024];

    while (fgets(line, sizeof(line), f)) 
    {
        size_t len = strlen(line);
        if (len && line[len - 1] == '\n')
            line[len - 1] = '\0';

        memset(reg, 0, sizeof(SharedRegion));
        strncpy(reg->buffer, line, sizeof(reg->buffer));
        reg->ready = 1;

        os_signal_ready();
        os_wait_child();

        if (reg->error) 
        {
            printf("Error: division by zero. Terminating.\n");
            break;
        }
    }

    fclose(f);
    os_cleanup();
    return 0;
}
