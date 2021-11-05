#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int arg, char *argv[])
{
    printf("EXECD_PGM.C\n");
    system("ps");
    printf("\n\nEnvironment Variables:\n");

    system("printenv SHELL");
    system("printenv HOME");
    system("printenv PWD");
    system("printenv PATH");
    system("printenv TEST1");

    return 0;
}