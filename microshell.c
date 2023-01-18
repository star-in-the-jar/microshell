#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>

/* for command input */
#define PATH_MAX_LENGTH 1024
#define COMMAND_MAX_LENGTH 1024
#define MAX_ARGS 128
#define MAX_ARG_LEN 256

void showOff();
void displayInfo();
void getCurrentWorkingDirectory(char *path, size_t maxSize);
void getCommandArguments(char **commArguments, int *argumentsNum);
void freeCommandArguments(char **commArguments);

/* print text */
void colorReset();
void colorHighlight();
void colorSuccess();
void colorWarning();
void colorError();

int main()
{
    /* declare variables */
    char *path = malloc(PATH_MAX_LENGTH);
    char *commArguments[MAX_ARGS];
    int argumentsNum = 0;

    /* welcome message */
    showOff();

    while (1)
    {
        /* display current path */
        getCurrentWorkingDirectory(path, PATH_MAX_LENGTH);
        colorHighlight();
        printf("MICRO [%s] $ ", path);
        colorReset();

        /* get user command and split it into arguments */
        getCommandArguments(commArguments, &argumentsNum);

        /* execute command based on the first argument */
        if (commArguments[0] == NULL)
        {
            continue;
        }
        else if (strcmp(commArguments[0], "cd") == 0)
        {
            /* if '~' or no arguments set first argument to $HOME */
            if (commArguments[1] == NULL || strcmp(commArguments[1], "~") == 0)
            {
                commArguments[1] = getenv("HOME");
            }
            /* if '-' set first argument to $OLDPWD */
            else if (strcmp(commArguments[1], "-") == 0)
            {
                if ((commArguments[1] = getenv("OLDPWD")) == NULL)
                {
                    colorError();
                    printf("Error in main(): env OLDPWD is not set\n");
                    colorReset();
                }
            }

            /* change directory */
            if (chdir(commArguments[1]) != 0)
            {
                colorError();
                printf("Error in main(): chdir() failure\n");
                colorReset();
            }

            /* update $OLDPWD */
            if (setenv("OLDPWD", path, 1) != 0)
            {
                colorError();
                printf("Error in main(): setenv() failure\n");
                colorReset();
            }
        }
        else if (strcmp(commArguments[0], "pwd") == 0)
        {
            printf("%s\n", path);
        }
        else if (strcmp(commArguments[0], "exit") == 0)
        {
            exit(0);
        }
        else if (strcmp(commArguments[0], "help") == 0)
        {
            showOff();
            displayInfo();
        }
        else
        {
            /* fork to run execvp */
            pid_t forkId = fork();

            if (forkId == -1)
            {
                colorError();
                printf("Error in main(): Fork failed\n");
                colorReset();
            }
            else if (forkId == 0)
            {
                if (execvp(commArguments[0], commArguments) == -1)
                {
                    colorError();
                    printf("Error in main(): exec* error\n");
                    colorReset();
                }
            }
            else
            {
                wait(NULL);
            }
        }
    }

    /* free memory allocated */
    freeCommandArguments(commArguments);
    free(path);

    return 0;
}

void getCurrentWorkingDirectory(char *path, size_t maxSize)
{
    if (getcwd(path, maxSize) == NULL)
    {
        colorError();
        perror("Error in getCurrentWorkingDirectory(): getcwd() failure\n");
        colorReset();
    }
}

void getCommandArguments(char **commArguments, int *argumentsNum)
{
    char *command = malloc(COMMAND_MAX_LENGTH);

    /* get input from user and remove new line char */
    fgets(command, COMMAND_MAX_LENGTH, stdin);
    size_t lastCharIndex = strcspn(command, "\n");
    command[lastCharIndex] = '\0';

    /* split command int arguments */
    char *token = malloc(MAX_ARG_LEN);
    int i = 0;

    token = strtok(command, " ");
    while (token != NULL)
    {
        /* check if argument length is lower than allowed */
        size_t tokenLen = strlen(token);
        if (tokenLen > MAX_ARG_LEN)
        {
            colorError();
            printf("Error: the given argument is too long\n");
            colorReset();
            return;
        }

        commArguments[i] = (char *)malloc(strlen(token) + 1);
        strcpy(commArguments[i], token);
        token = strtok(NULL, " ");
        i++;
    }

    *argumentsNum = i;
    commArguments[i] = NULL;

    /* free memory*/
    free(command);
}

void freeCommandArguments(char **commArguments)
{
    for (int j = 0; j < MAX_ARGS; j++)
    {
        if (commArguments[j] == NULL)
        {
            break;
        }

        free(commArguments[j]);
        commArguments[j] = NULL;
    }
}

/* functions for color change*/

void colorError()
{
    printf("\033[0;31m");
}

void colorSuccess()
{
    printf("\033[0;32m");
}

void colorWarning()
{
    printf("\033[0;33m");
}

void colorHighlight()
{
    printf("\033[0;35m");
}

void colorReset()
{
    printf("\033[0;00m");
}

/* functions printing text */

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
}

void displayInfo()
{
    printf("Dostępne komendy:\n");
    printf("\n");
    printf("help  ==> wyświetlenie pomocy\n");
    printf("\n");
    printf("exit  ==> zamknięcie programu\n");
    printf("\n");
    printf("cd  ==> zmiana katalogu roboczego\n");
    printf("    cd            --> przejście do katalogu domowego\n");
    printf("    cd ~          --> przejście do katalogu domowego\n");
    printf("    cd -          --> przejście do poprzedniego katalogu\n");
    printf("    cd /path      --> przejście do katalogu o ścieżce absolutnej\n");
    printf("    cd path       --> przejście do katalogu o ścieżce relatywnej\n");
    printf("\n");
    printf("ls  ==> wyświetlenie zawartości folderu\n");
    printf("    ls -l         --> przejście do katalogu domowego\n");
    printf("    ls -a         --> przejście do katalogu domowego\n");
    printf("    ls -h         --> przejście do katalogu domowego\n");
    printf("    ls -i         --> przejście do katalogu domowego\n");
    printf("    ls --color    --> przejście do katalogu domowego\n");
    printf("\n");
    printf("Autorem programu Microshell jest Stanisław Jarocki.\n");
}