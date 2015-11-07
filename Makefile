DIR 	= src
TARGET 	= rshell
BIN	= bin/

CC	= g++
WFLAGS	= -Wall -Werror
LFLAGS	=
CFLAGS	= -ansi -pedantic $(WFLAGS)
LIBS	=

HDRS	= $(shell find $(DIR) -name '*.h')
SRCS	= $(shell find $(DIR) -name '*.cpp')
OBJS	= $(SRCS:.cpp=.o) $(shell find $(DIR) -name '*.o')

all: clean rshell

rshell: 
	mkdir -p bin
	$(CC) $(CFLAGS) $(LIBS) $(SRCS) -o $(BIN)$(TARGET)

clean: 
	rm -rf $(OBJS) $(BIN)$(TARGET) bin
