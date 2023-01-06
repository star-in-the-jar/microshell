#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

void getCurrentWorkingDirectory(char *path, size_t size);

int main()
{
    size_t PATH_MAX_LENGTH = 1000;
    char *path = malloc(PATH_MAX_LENGTH);

    while(1) {
        getCurrentWorkingDirectory(path, PATH_MAX_LENGTH);
        printf("[%s] $ ", path);

        char *enteredCommand = malloc(PATH_MAX_LENGTH);
        scanf("%s", enteredCommand);
    }

    free(path);

    return 0;
}

void getCurrentWorkingDirectory(char *path, size_t MAX_LENGTH)
{
    char *getcwd(char *buf, size_t size);
    
    if (getcwd(*(&path), MAX_LENGTH) == NULL) {
        perror("Error occured in getCurrentWorkingDirectory()");
    }
}
