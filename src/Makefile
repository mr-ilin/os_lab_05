CC = clang

CC_FLAGS = -pedantic -Wall
LD_FLAGS = -L. -ltools1

CC_LIB_FLAGS = -c -pedantic -Wall -fPIC
LD_LIB_FLAGS = -shared

EXECUTABLE1 = task1
EXECUTABLE2 = task

SRC_EXE1 = task1.c
SRC_EXE2 = task2.c
OBJ_EXE1 = $(SRC_EXE1:.c=.o)
OBJ_EXE2 = $(SRC_EXE2:.c=.o)

SRC_LIB1 = ./libs/my_lib1.c
SRC_LIB2 = ./libs/my_lib1.c
OBJ_LIB1 = $(SRC_LIB1:.c=.o)
OBJ_LIB2 = $(SRC_LIB2:.c=.o)
SO_LIB1  = libtools1.so
SO_LIB2  = libtools2.so

all: $(EXECUTABLE1) #$(EXECUTABLE2)

$(EXECUTABLE1) : $(SRC_EXE1) $(SO_LIB1)
	$(CC) $(CC_FLAGS) $(SRC_EXE1) -o $(EXECUTABLE1) $(LD_FLAGS)

$(SO_LIB1) : $(OBJ_LIB1)
	$(CC) $< -o $@ $(LD_LIB_FLAGS)

$(OBJ_LIB1) : $(SRC_LIB1)
	$(CC) $(CC_LIB_FLAGS) $< -o $@

# gcc -c -fPIC hello.c -o hello.o
# gcc hello.o -shared -o libhello.so

# This is a colon separated list of directories that contain libraries. 
# The dynamic linker searches these directories before it searches the default locations for libraries. 
# It allows you to test new versions of existing libraries.

clean:
	rm -f *.o *.so $(EXECUTABLE1) $(EXECUTABLE2)
