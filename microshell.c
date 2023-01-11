#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH_MAX_LENGTH 1024
#define COMMAND_MAX_LENGTH 1024
#define MAX_ARGS 128
#define MAX_ARG_LEN 256

void showOff();
void getCurrentWorkingDirectory(char *path, size_t maxSize);

int main()
{
    /* declare variables */
    char *path = malloc(PATH_MAX_LENGTH);
    char *command = malloc(COMMAND_MAX_LENGTH);
    char *commArgv[MAX_ARGS];

    /* welcome message */
    // showOff();

    while (1)
    {
        /* display current path */
        getCurrentWorkingDirectory(path, PATH_MAX_LENGTH);
        printf("MICRO [%s] $ ", path);

        /* get user command */
        fgets(command, COMMAND_MAX_LENGTH, stdin);
        size_t lastCharIndex = strcspn(command, "\n");
        command[lastCharIndex] = 0;

        /* split line input into array of arguments */
        char *token;
        int i = 0;

        token = strtok(command, " ");
        while (token != NULL)
        {
            /* check if argument length is lower than allowed */
            size_t tokenLen = strlen(token);
            if (tokenLen > MAX_ARG_LEN) {
                printf("Error in (future) getArguments(): the given argument is too long");
                return 1;
            }

            commArgv[i] = (char *)malloc(strlen(token) + 1);
            strcpy(commArgv[i], token);
            token = strtok(NULL, " ");
            i++;
        }

        /* point the end of array */
        commArgv[i] = NULL;

        /* print all arguments */
        for (int j = 0; j < MAX_ARGS; j++)
        {
            if (commArgv[j] == NULL)
            {
                break;
            }

            printf("Argument %d: %s\n", j + 1, commArgv[j]);
        }

        /* free memory allocated for commArgv array */
        for (int j = 0; j < MAX_ARGS; j++)
        {
            if (commArgv[j] == NULL)
            {
                break;
            }
            free(commArgv[j]);
            commArgv[j] = NULL;
        }
    }

    free(path);
    free(command);

    return 0;
}
//     /* execute command based on first argument */
//     if (strlen(commArgv[0]) == 0)
//     {
//         exit(0);
//     }
//     else if (strcmp(commArgv[0], "exit") == 0)
//         exit(0);
//     else if (strcmp(commArgv[0], "pwd") == 0)
//     {
//         printf("%s\n", path);
//         getchar();
//     }
//     else if (strcmp(commArgv[0], "ls") == 0)
//     {
//         pid_t pid = fork();

//         if (pid == -1)
//         {
//             printf("Error in ls: fork() returned -1\n");
//         }
//         else if (pid == 0)
//         {
//             execl("/bin/ls", commArgv[0], commArgv[1], NULL);
//         }
//         else
//         {
//             wait(NULL);
//         }
//     }
//     else if (strcmp(commArgv[0], "cd") == 0)
//     {
//         /* if no arguments go to home directory */
//         // if (ArgvNum == 0)
//         // {
//         //     printf("No arguments given, going to home directory\n");
//         //     char *homePath = getenv("HOME");
//         //     for (int i = 0; i < strlen(homePath); i++)
//         //     {
//         //         commArgv[1][i] = homePath[i];
//         //     }
//         // }

//         /* try to change directory */
//         int result = chdir(commArgv[1]);

//         /* error handling */
//         if (result == -1)
//         {
//             perror("Error in cd: wrong argument given");
//         }
//         else
//         {
//             printf("Changed directory to %s\n", commArgv[1]);
//         }
//     }
//     else
//     {
//         printf("Unknown command: %s\n", commArgv[0]);
//     }

//     free(path);
//     free(command);
// }
//     return 0;
// }

void getCurrentWorkingDirectory(char *path, size_t maxSize)
{
    char *getcwd(char *buf, size_t size);

    if (getcwd(path, maxSize) == NULL)
    {
        perror("Error in getCurrentWorkingDirectory()");
    }
}

void getInput(char *command, size_t maxSize)
{
    fgets(command, maxSize, stdin);
}

void splitCommand(char *command, char **commArgv)
{
    char *token;
    int i = 0;

    token = strtok(command, " ");
    while (token != NULL)
    {
        commArgv[i++] = token;
        // printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}
// int commCh = 0, ArgvNum = 0, argCh = 0;

// while (commCh != '\n')
// {
//     /* terminate if user separated arguments with more than one space*/
//     if (command[commCh] == ' ' && command[commCh + 1] == ' ')
//     {
//         printf("Error: Too many spaces separating arguments\n");
//         exit(1);
//     }

//     /* split input by space into array of arguments*/
//     if (command[commCh] == ' ')
//     {
//         commArgv[ArgvNum][argCh] = '\0';
//         ArgvNum++;
//         argCh = 0;
//     }
//     else
//     {
//         commArgv[ArgvNum][argCh] = command[commCh];
//         argCh++;
//     }

//     commCh++;
// }

void showOff()
{
    printf("\n");
    printf("\n");
    printf("\n");
    printf("    MMMMMMMM               MMMMMMMM iiii                                                                      hhhhhhh                              llllllllllllll ");
    printf("\n");
    printf("    M:::::::M             M:::::::Mi::::i                                                                     h:::::h                              l:::::ll:::::l ");
    printf("\n");
    printf("    M::::::::M           M::::::::M iiii                                                                      h:::::h                              l:::::ll:::::l ");
    printf("\n");
    printf("    M:::::::::M         M:::::::::M                                                                           h:::::h                              l:::::ll:::::l ");
    printf("\n");
    printf("    M::::::::::M       M::::::::::iiiiiii    cccccccccccccccrrrrr   rrrrrrrrr     ooooooooooo      ssssssssss  h::::h hhhhh          eeeeeeeeeeee   l::::l l::::l ");
    printf("\n");
    printf("    M:::::::::::M     M:::::::::::i:::::i  cc:::::::::::::::r::::rrr:::::::::r  oo:::::::::::oo  ss::::::::::s h::::hh:::::hhh     ee::::::::::::ee l::::l l::::l ");
    printf("\n");
    printf("    M:::::::M::::M   M::::M:::::::Mi::::i c:::::::::::::::::r:::::::::::::::::ro:::::::::::::::ss:::::::::::::sh::::::::::::::hh  e::::::eeeee:::::el::::l l::::l ");
    printf("\n");
    printf("    M::::::M M::::M M::::M M::::::Mi::::ic:::::::cccccc:::::rr::::::rrrrr::::::o:::::ooooo:::::s::::::ssss:::::h:::::::hhh::::::he::::::e     e:::::l::::l l::::l ");
    printf("\n");
    printf("    M::::::M  M::::M::::M  M::::::Mi::::ic::::::c     cccccccr:::::r     r:::::o::::o     o::::os:::::s  ssssssh::::::h   h::::::e:::::::eeeee::::::l::::l l::::l ");
    printf("\n");
    printf("    M::::::M   M:::::::M   M::::::Mi::::ic:::::c             r:::::r     rrrrrro::::o     o::::o  s::::::s     h:::::h     h:::::e:::::::::::::::::el::::l l::::l ");
    printf("\n");
    printf("    M::::::M    M:::::M    M::::::Mi::::ic:::::c             r:::::r           o::::o     o::::o     s::::::s  h:::::h     h:::::e::::::eeeeeeeeeee l::::l l::::l ");
    printf("\n");
    printf("    M::::::M     MMMMM     M::::::Mi::::ic::::::c     cccccccr:::::r           o::::o     o::::ssssss   s:::::sh:::::h     h:::::e:::::::e          l::::l l::::l ");
    printf("\n");
    printf("    M::::::M               M::::::i::::::c:::::::cccccc:::::cr:::::r           o:::::ooooo:::::s:::::ssss::::::h:::::h     h:::::e::::::::e        l::::::l::::::l");
    printf("\n");
    printf("    M::::::M               M::::::i::::::ic:::::::::::::::::cr:::::r           o:::::::::::::::s::::::::::::::sh:::::h     h:::::he::::::::eeeeeeeel::::::l::::::l");
    printf("\n");
    printf("    M::::::M               M::::::i::::::i cc:::::::::::::::cr:::::r            oo:::::::::::oo s:::::::::::ss h:::::h     h:::::h ee:::::::::::::el::::::l::::::l");
    printf("\n");
    printf("    MMMMMMMM               MMMMMMMiiiiiiii   ccccccccccccccccrrrrrrr              ooooooooooo    sssssssssss   hhhhhhh     hhhhhhh   eeeeeeeeeeeeeelllllllllllllll");
    printf("\n");

    printf("     _                 _              _     _                    _                      _    _ ");
    printf("\n");
    printf("    | |__  _   _   ___| |_ __ _ _ __ (_)___| | __ ___      __   (_) __ _ _ __ ___   ___| | _(_)");
    printf("\n");
    printf("    | '_ \\| | | | / __| __/ _` | '_ \\| / __| |/ _` \\ \\ /\\ / /   | |/ _` | '__/ _ \\ / __| |/ | |");
    printf("\n");
    printf("    | |_) | |_| | \\__ | || (_| | | | | \\__ | | (_| |\\ V  V /    | | (_| | | | (_) | (__|   <| |");
    printf("\n");
    printf("    |_.__/ \\__, | |___/\\__\\__,_|_| |_|_|___|_|\\__,_| \\_/\\_/    _/ |\\__,_|_|  \\___/ \\___|_|\\_|_|");
    printf("\n");
    printf("           |___/                                              |__/                             ");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
}