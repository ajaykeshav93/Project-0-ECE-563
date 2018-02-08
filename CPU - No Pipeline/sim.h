#ifndef SIM_H_
#define SIM_H_

#include <stdio.h>
#include <string>
#include <list>

#define BASE_ADDRESS 0x10000000
#define UNDEFINED 0xFFFFFFFF //constant used to initialize registers
#define NUM_SP_REGISTERS 9
#define NUM_GP_REGISTERS 32
#define NUM_OPCODES 10

typedef enum {PC, NPC, IR, A, B, IMM, COND, ALU_OUTPUT, LMD} sp_register_t;

typedef enum {LW, SW, ADD, ADDI, SUB, SUBI, XOR, BLTZ, BNEZ, EOP} opcode_t;

typedef enum   {terminated,in_progress} fsm_state;

typedef struct finite_state_machine {
    
    fsm_state s;
    
}fsm;


class pipeline_reg
{
	unsigned PC,NPC,A,B,IMM,COND,ALU_OUTPUT,LMD;
};

pipeline_reg IF_ID;
pipeline_reg ID_EX;
pipeline_reg EX_MEM;
pipeline_reg MEM_WB;




class sim{

	/* Add the data members required by your simulator's implementation here */
	
         int clock_cycles;
        
         int num_instructions;
	//data memory - should be initialize to all 0xFF
	unsigned char *data_memory;

	//memory size in bytes
	unsigned data_memory_size;
        
         // Array of integers to represent general purpose registers
        unsigned regs[32];
        
        // Special purpose registers
        unsigned sp_PC,sp_NPC,sp_A,sp_B,sp_IMM,sp_COND,sp_ALU_OUTPUT,sp_LMD;

public:

	//instantiates the simulator with a data memory of given size (in bytes)
	sim(unsigned data_mem_size);
	
	//de-allocates the simulator
	~sim();

	//loads the assembly program in file "filename" in instruction memory at the specified address
	void load_program(const char *filename, unsigned base_address=0x0);

	//runs the simulator for "cycles" clock cycles (run the program to completion if cycles=0) 
	void run(unsigned cycles=0);
	
	//resets the state of the simulator
        /* Note: registers should be reset to UNDEFINED value */
	void reset();

	//returns value of the specified special purpose register
	/* Note: you are allowed to use a custom format for the IR register.
           Therefore, the test cases won't check the value of IR using this method. 
	   You can add an extra method to retrieve the content of IR */
	unsigned get_sp_register(sp_register_t reg);

	//returns value of the specified general purpose register
	unsigned get_gp_register(unsigned reg);

	//returns the IPC
	float get_IPC();

	//returns the number of instructions fully executed
	unsigned get_instructions_executed();

	//prints the content of the data memory within the specified address range
	void print_memory(unsigned start_address, unsigned end_address);

	// writes an integer value to data memory at the specified address (use little-endian format: https://en.wikipedia.org/wiki/Endianness)
	void write_memory(unsigned address, unsigned value);

	//prints the values of the registers 
	void print_registers();
        
         fsm engine(unsigned c);

};


class instruction {
    
    friend class sim;
    opcode_t opcode;
    unsigned char bin_op;
    int address;
    int source_1_index;
    int source_2_index;
    int destination_index;
    int imm;
    int base_reg_index;
    int offset;
    int target_address;
    std::string label;
    
    
};

class Entry {
    
public :
    std::string label;
    unsigned target;
    
public :
    void insert_elt(Entry&);
    unsigned find_elt(std::string&);
    
};

std::list <Entry> branches;

void Entry::insert_elt(Entry& e) {
    branches.push_front(e);
}

unsigned Entry::find_elt(std::string& s) {
    
    typedef std::list <Entry> :: iterator LI;
    for ( LI i = branches.begin(); i!= branches.end(); ++i )
    {
        Entry& e = *i;
        if (s == e.label)
            return e.target;
    }
    
    return 0;
}




#endif /*SIM_H_*/

