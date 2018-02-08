CC = g++
OPT = -g  
WARN = -Wall
CFLAGS = $(OPT) $(WARN) 

# List all your .cc files here (source files, excluding header files)
SIM_SRC = sim.cc main.cc 

# List corresponding compiled object files here (.o files)
SIM_OBJ = sim.o main.o 

 
#################################

# default rule
all: sim


# rule for making sim_cache
sim: $(SIM_OBJ)
	$(CC) -o sim $(CFLAGS) $(SIM_OBJ)


# generic rule for converting any .cc file to any .o file
.cc.o:
	$(CC) $(CFLAGS)  -c $*.cc


# type "make clean" to remove all .o files plus the sim binary
clean:
	rm -f *.o sim


# type "make clobber" to remove all .o files
clobber:
	rm -f *.o

