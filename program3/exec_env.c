#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int do_exec(int varg_count, char *pgm_path, char *SHELL, char *HOME, char *PWD, char *PATH)
{
    printf("Attempting to exec:\n\n");
    if(execl(pgm_path, SHELL, HOME, PWD, PATH, (char *)0) == -1)
    {
        //Prints error and exits program
        perror("exec failed");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    printf("EXEC_ENV.C\n");
    system("ps");
    printf("\n");

    //Environment Variables
    char SHELL[50] = "SHELL=/bin/bash";
    char HOME[50] = "HOME=/home/austinlefty";
    char PWD[50] = "PWD=/home/austinlefty/src";
    char PATH[50] = "PATH=usr/bin";

    //Exec Program
    do_exec(4, "./execd_pgm", SHELL, HOME, PWD, PATH);

    return 0;
}