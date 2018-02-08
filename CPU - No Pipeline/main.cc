#include "sim.h"
#include <iostream>
#include <stdlib.h>
#include <list>

using namespace std;

/* Test case for the simulator.
   Feel free to create additional test cases to debug and test your simulator's implementation */ 



int main(){

	unsigned i, j;

	// instantiates the simulator with a 1MB data memory
	sim *mips = new sim(1024*1024);

	//loads program in instruction memory at address 0x10000000
	mips->load_program("asm/code.asm", 0x10000000);

	//prints the value of the registers
	mips->print_registers();

	//initialize data memory and prints its content (for the specified address ranges)
	for (i = 0xA000, j=1; i<0xA020; i+=4, j+=1) mips->write_memory(i,j);
	mips->print_memory(0xA000, 0xA028);
	mips->print_memory(0xB000, 0xB028);

	// executes the program	
	cout << "\nSTARTING THE PROGRAM..." << endl << endl;

	for (i=0; i<15; i++){
		mips->run(5);
		mips->print_registers();
		cout << endl;
	}

        
	mips->run(2);

	mips->run(); // runs the program to completion

	//prints the value of registers and data memory
	mips->print_registers();
	mips->print_memory(0xA000, 0xA028);
	mips->print_memory(0xB000, 0xB028);
	
	cout << endl;

	// prints the number of instructions executed and IPC
	cout << "Instruction executed = " << dec  << mips->get_instructions_executed() << endl;
	cout << "IPC = " << dec << mips->get_IPC() << endl;
}
