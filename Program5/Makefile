# Program 5
CC = gcc
LINKER = gcc

# compiler/linker flags
CC_FLAGS = -g -Wall 
LINKER_FLAGS = -g

# files removal
RM = rm -f

# library to use when linking the main program
LIBS = -lpthread

# object files
OBJS = worker_thread.o worker_thread_pool.o main.o request_queue.o

# output exeutable program
EXEC = request_server

all: ${EXEC}

${EXEC}: ${OBJS}
	${LINKER} ${LINKER_FLAGS} ${OBJS} ${LIBS} -o ${EXEC}

%.o: %.c
	${CC} ${CC_FLAGS} -c $<

clean:
	${RM} ${OBJS} ${EXEC}
