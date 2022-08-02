#OBJS defines files to compile
OBJS = recursive_window_count.cpp XWindowList.cpp
CC = g++
COMPILER_FLAGS = -g -Wall -Wextra -Wpedantic -std=c++17
LINKER_FLAGS = -lX11 
OBJ_NAME = aout

all : $(OBJS) 
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
