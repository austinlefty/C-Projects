#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../common.h"

const char *pdf_reader_app="/usr/bin/evince";

static int exec_pdf_reader_app(char *pdfdoc, int pid)
{
	if(pid < 0) //Prints error if fork fails
		FATAL("Failed to fork\n");

	else if(pid == 0) //Only execs if it is the child process
	{
		char * const pdf_argv[] = {"evince", pdfdoc, 0};

		if (execv(pdf_reader_app, pdf_argv) < 0) 
		{
			WARN("execv failed\n");
			return -1;
		}
	}
	
	return 0;
}

int main(int argc, char **argv)
{
	printf("We are in the parent and this should print only once\n");

	int pid = fork();
	if (argc < 2) {
		fprintf(stderr, "Usage: %s {pathname_of_doc.pdf}\n"
			, argv[0]);
		exit(EXIT_FAILURE);
	}

	if (exec_pdf_reader_app(argv[1], pid) < 0)
		FATAL("exec pdf function failed\n");
	
	return 0;
}
