CC = clang

CC_FLAGS = -pedantic -Wall
LD_FLAGS = -L. 

CC_LIB_FLAGS = -c -pedantic -Wall -fPIC
LD_LIB_FLAGS = -shared

EXECUTABLE1 = task1
EXECUTABLE2 = task2

SRC_EXE1 = task1.c
SRC_EXE2 = task2.c
OBJ_EXE1 = $(SRC_EXE1:.c=.o)
OBJ_EXE2 = $(SRC_EXE2:.c=.o)

LIB1     = -ltools1
LIB2     = -ltools2
SRC_LIB1 = ./libs/my_lib1.c ./libs/strconv.c
SRC_LIB2 = ./libs/my_lib2.c ./libs/stack.c
ND_SRC_LIB1 = $(notdir $(SRC_LIB1))
ND_SRC_LIB2 = $(notdir $(SRC_LIB2))
OBJ_LIB1 = $(ND_SRC_LIB1:.c=.o)
OBJ_LIB2 = $(ND_SRC_LIB2:.c=.o)
SO_LIB1  = libtools1.so
SO_LIB2  = libtools2.so

all: $(EXECUTABLE1) $(EXECUTABLE2)

$(EXECUTABLE1) : $(SRC_EXE1) $(SO_LIB1)
	$(CC) $(CC_FLAGS) $(SRC_EXE1) -o $(EXECUTABLE1) $(LD_FLAGS) $(LIB1)

$(EXECUTABLE2) : $(SRC_EXE2) $(SO_LIB2)
	$(CC) $(CC_FLAGS) $(SRC_EXE2) -o $(EXECUTABLE2) $(LD_FLAGS) $(LIB2)

$(SO_LIB1) : $(OBJ_LIB1)
	$(CC) $^ -o $@ $(LD_LIB_FLAGS)

$(OBJ_LIB1) : $(SRC_LIB1)
	$(CC) $(CC_LIB_FLAGS) $^

$(SO_LIB2) : $(OBJ_LIB2)
	$(CC) $^ -o $@ $(LD_LIB_FLAGS)

$(OBJ_LIB2) : $(SRC_LIB2)
	$(CC) $(CC_LIB_FLAGS) $^

clean:
	rm -f *.o *.so $(EXECUTABLE1) $(EXECUTABLE2)
