#include "sim.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <map>
#include <valarray>

using namespace std;

//used for debugging purposes
static const char *reg_names[NUM_SP_REGISTERS] = {"PC", "NPC", "IR", "A", "B", "IMM", "COND", "ALU_OUTPUT", "LMD"};

string str[15];             // Array of strings to collect parsed string from file
instruction instr[15];      // Array of instructions stored in memory
instruction sp_IR;          // Instruction Register - Holds data of class instruction


Entry k;


// Constructor for initializing the simulator variables
sim::sim(unsigned mem_size){
    
    // 1. Initialize CPU General Purpose Registers 
    int i;
    for (i=0;i<32;i++)
    {
        regs[i] = UNDEFINED;
    }
    
    // 2. Initialize Data Memory Size
    
    data_memory_size = mem_size;
    
    // 3. Initialize Data Memory
    
   data_memory = new unsigned char[data_memory_size];
   for (unsigned z=0;z < data_memory_size; z++)
   {
       data_memory[z] = 0xFF;
   }
   
   // 4. Initialize Special Purpose Registers 
   
   sp_PC = BASE_ADDRESS;
   sp_NPC = 0;
   sp_A = 0;
   sp_B = 0;
   sp_LMD = 0;
   sp_IMM = 0;
   sp_ALU_OUTPUT =0;
   sp_COND = 0;
   
 
   clock_cycles = 0;
   
   num_instructions = 0;
    
    cout << "Simulator Initialization Complete..\n";
  
}
	
// Destructor to free up heap allocated storage 

sim::~sim(){
    
    delete[] data_memory;
}

void sim::load_program(const char *filename, unsigned base_address){
    
    int n=0;
    int x=0,addr;
    int y=0;
    ifstream assembly (filename);
    addr = base_address;
    if (assembly.is_open())
    {
     
        cout << "File Opened Successfully..\n"; 
        do
        {
            getline (assembly,str[x]);
            instr[x].address = addr;
            addr = addr + 0x04;
            x++;
        
        }while (str[x-1] != "EOP");
        
        cout << "Number of lines of assembly code is : \t" << x << endl;
        
        assembly.close();
        
        // Now str[] array contains instructions as strings each of variable length
        // They have to be converted to a 32-bit type to fit in the instruction register
        // Done by encoding parts of string to appropriate fields in IR
        
        do
        {
           // For each string 
           n = str[y].length();
           char char_array[n+1]; 
     
           // copying the contents of the 
           // string to char array
           strcpy(char_array, str[y].c_str()); 
            
           char *token = strtok(char_array, " ");
           cout << token << endl;
           // Keep printing tokens while one of the
           
           // delimiters present in str[].
           while (token != NULL)
            {
                         if ( strcmp(token,"ADD") == 0)
                         {
                                instr[y].opcode = ADD;
                                instr[y].bin_op = 0;
                                token = strtok(NULL," ");
                                cout << token << endl;
                                            
                                instr[y].destination_index = atoi (token+1);
                                cout << "destination reg index :" << dec <<   instr[y].destination_index << endl;
                                            

                                token = strtok(NULL," ");
                                cout << token << endl;
                                instr[y].source_1_index = atoi (token+1);

                                cout << "source 1 index :" << dec << instr[y].source_1_index << endl;

                                token = strtok (NULL, " ");
                                cout << token << endl;
                                instr[y].source_2_index = atoi (token+1);

                                cout << "source 2 index :" << dec <<  instr[y].source_2_index << endl;
                                
                                y++;
                                        
                        }
                         
                         
                         else if ( strcmp(token,"SUB") == 0)
                         {
                                instr[y].opcode = SUB;
                                instr[y].bin_op = 1;
                                token = strtok(NULL," ");
                                cout << token << endl;
                                            
                                instr[y].destination_index = atoi (token+1);
                                cout << "destination reg index :" << dec <<   instr[y].destination_index << endl;
                                            

                                token = strtok(NULL," ");
                                cout << token << endl;
                                instr[y].source_1_index = atoi (token+1);

                                cout << "source 1 index :" << dec << instr[y].source_1_index << endl;

                                token = strtok (NULL, " ");
                                cout << token << endl;
                                instr[y].source_2_index = atoi (token+1);

                                cout << "source 2 index :" << dec <<  instr[y].source_2_index << endl;
                                
                                y++;
                                        
                        }
                         
                         
                         
                         else if ( strcmp(token,"XOR") == 0)
                         {
                                instr[y].opcode = XOR;
                                instr[y].bin_op = 2;
                                token = strtok(NULL," ");
                                cout << token << endl;
                                            
                                instr[y].destination_index = atoi (token+1);
                                cout << "destination reg index :" <<  dec << instr[y].destination_index << endl;
                                            

                                token = strtok(NULL," ");
                                cout << token << endl;
                                instr[y].source_1_index = atoi (token+1);

                                cout << "source 1 index :" << dec << instr[y].source_1_index << endl;

                                token = strtok (NULL, " ");
                                cout << token << endl;
                                instr[y].source_2_index = atoi (token+1);

                                cout << "source 2 index :" << dec <<  instr[y].source_2_index << endl;
                                
                                y++;
                                        
                        }
              
                         
                         else if ( strcmp(token,"ADDI") == 0)
                         {
                                instr[y].opcode = ADDI;
                                instr[y].bin_op = 3;
                                token = strtok(NULL," ");
                                cout << token << endl;
                                            
                                instr[y].destination_index = atoi (token+1);
                                cout << "destination reg index :" << dec <<   instr[y].destination_index << endl;
                                            

                                token = strtok(NULL," ");
                                cout << token << endl;
                                instr[y].source_1_index = atoi (token+1);

                                cout << "source 1 index :" << dec << instr[y].source_1_index << endl;

                                token = strtok (NULL, " ");
                                cout << token << endl;
                                instr[y].imm = (unsigned)strtol ((token+2),NULL,16);

                                cout << "source 2 index :" << hex <<  instr[y].imm << endl;
                                
                                y++;
                                        
                        }
                         
                         
                         
                         else if ( strcmp(token,"SUBI") == 0)
                         {
                                instr[y].opcode = SUBI;
                                instr[y].bin_op = 4;
                                token = strtok(NULL," ");
                                cout << token << endl;
                                            
                                instr[y].destination_index = atoi (token+1);
                                cout << "destination reg index :" << dec <<   instr[y].destination_index << endl;
                                            

                                token = strtok(NULL," ");
                                cout << token << endl;
                                instr[y].source_1_index = atoi (token+1);

                                cout << "source 1 index :" << dec << instr[y].source_1_index << endl;

                                token = strtok (NULL, " ");
                                cout << token << endl;
                                instr[y].imm = (unsigned)strtol ((token+2),NULL,16);

                                cout << "source 2 index :" << hex <<  instr[y].imm << endl;
                                
                                y++;
                                        
                        }
                         
                         
                         else if ( strcmp(token,"LW") == 0)
                         {
                                instr[y].opcode = LW;
                                instr[y].bin_op = 5;
                                token = strtok(NULL," ");
                                cout << token << endl;
                                            
                                instr[y].destination_index = atoi (token+1);
                                cout << "destination reg index :" << dec <<   instr[y].destination_index << endl;
                                            

                                token = strtok(NULL,"(");
                                cout << token << endl;
                                instr[y].offset = atoi (token+1);

                                cout << "offset :" << dec << instr[y].offset << endl;

                                token = strtok (NULL, ")");
                                cout << token << endl;
                                instr[y].base_reg_index = atoi (token+1);

                                cout << "base register index :" << dec <<  instr[y].base_reg_index << endl;
                                
                                y++;
                                        
                        }
                         
                         
                         else if ( strcmp(token,"SW") == 0)
                         {
                                instr[y].opcode = SW;
                                instr[y].bin_op = 6;
                                token = strtok(NULL," ");
                                cout << token << endl;
                                            
                                instr[y].source_1_index = atoi (token+1);
                                cout << "destination reg index :" << dec <<   instr[y].source_1_index << endl;
                                            

                                token = strtok(NULL,"(");
                                cout << token << endl;
                                instr[y].offset = atoi (token);

                                cout << "offset :" << dec << instr[y].offset << endl;

                                token = strtok (NULL, ")");
                                cout << token << endl;
                                instr[y].base_reg_index = atoi (token+1);

                                cout << "base register index :" << dec <<  instr[y].base_reg_index << endl;
                                
                                y++;
                                        
                        }
                    
                         
                        else if(strcmp(token,"BLTZ") == 0 ) 
                         {
                                instr[y].opcode = BLTZ;
                                instr[y].bin_op = 7;
                                token = strtok(NULL," ");
                                cout << token << endl;
                                            
                                instr[y].source_1_index = atoi (token+1);
                                cout << "source reg index :" << dec <<    instr[y].source_1_index << endl;
                                            

                                token = strtok(NULL," ");
                                cout << token << endl;
                                instr[y].label = token;

                                y++;
                                        
                        }
                         
                         else if(strcmp(token,"BNEZ") == 0 ) 
                         {
                                instr[y].opcode = BNEZ;
                                instr[y].bin_op = 8;
                                token = strtok(NULL," ");
                                cout << token << endl;
                                            
                                instr[y].source_1_index = atoi (token+1);
                                cout << "source reg index :" << dec <<  instr[y].source_1_index << endl;
                                            

                                token = strtok(NULL," ");
                                cout << token << endl;
                                instr[y].label = token;

                                y++;
                                        
                        }
                         
                        else if (strcmp(token,"EOP") == 0)
                        {
                            instr[y].opcode = EOP;
                            y++;
                        }
                        else
                        {
                            // If its a labeled instruction , push elements into list
                  
                            k.label = token;
                            k.target = instr[y].address;
                            k.insert_elt(k);
                            
                        }
                          
                         
                         
                token = strtok(NULL, " ");
            }
            
            
  
       
        }while (str[y-1] != "EOP");
        
        

    }
    else 
    {
        cout << "Error opening file.\n";
        cout << "Aborting Simulator....\n";
    }

}

void sim::run(unsigned cycles){
    
    fsm status;
    status.s = in_progress;
    while (status.s != terminated)
    {
        
        status = engine(cycles);
        
    }
    
    cout << num_instructions << endl;
    
}
	
void sim::reset(){
}

unsigned sim::get_sp_register(sp_register_t reg){
    
    switch (reg)
    {
        case PC         :                       return sp_PC;
        case NPC        :                       return sp_NPC;
        case A          :                       return sp_A;
        case B          :                       return sp_B;
        case IMM        :                       return sp_IMM;
        case COND       :                       return sp_COND;
        case ALU_OUTPUT :                       return sp_ALU_OUTPUT;
        case LMD        :                       return sp_LMD;
        default         :                       return 0;
    }
	return 0; //please modify
}

unsigned sim::get_gp_register(unsigned reg){
    
    return regs[reg]; //please modify
}

float sim::get_IPC(){
    
    float ipc ;
    ipc = (float)num_instructions / (float)clock_cycles;
    cout << "ipc is :" << ipc;
    cout << num_instructions << endl;
    cout << clock_cycles << endl;
    return ipc;//please modify
}

unsigned sim::get_instructions_executed(){
	return num_instructions; //please modify
}

void sim::print_memory(unsigned start_address, unsigned end_address){
	cout << "data_memory[0x" << hex << setw(8) << setfill('0') << start_address << ":0x" << hex << setw(8) << setfill('0') <<  end_address << "]" << endl;
	unsigned i;
	for (i=start_address; i<end_address; i++){
		if (i%4 == 0) cout << "0x" << hex << setw(8) << setfill('0') << i << ": "; 
		cout << hex << setw(2) << setfill('0') << int(data_memory[i]) << " ";
		if (i%4 == 3) cout << endl;
	} 
}

void sim::write_memory(unsigned address, unsigned value){
}

void sim::print_registers(){
	cout << "Special purpose registers:" << endl;
        unsigned i;
	for (i=0; i< NUM_SP_REGISTERS; i++)
		if ((sp_register_t)i != IR && get_sp_register((sp_register_t)i)!=UNDEFINED) cout << reg_names[i] << " = " << dec <<  get_sp_register((sp_register_t)i) << hex << " / 0x" << get_sp_register((sp_register_t)i) << endl;
	cout << "General purpose registers:" << endl;
	for (i=0; i< NUM_GP_REGISTERS; i++)
		if (get_gp_register(i)!=UNDEFINED) cout << "R" << dec << i << " = " << get_gp_register(i) << hex << " / 0x" << get_gp_register(i) << endl;
}


fsm sim::engine(unsigned c){
    
   
    static int n=0;
    static unsigned number_of_cycles =0;
    static fsm current_status;
    static enum { fetch , decode , execute , mem_access , write_back } exec_state = fetch;
    static int value=0;
    static int mask=0;
  
    //objects for each kind of instruction
    
    switch (exec_state)
    {
        case fetch :
        {
            cout << "Fetching Instruction..\n";
            if ( (number_of_cycles != c) || (c==0) )
            {
                n = (sp_PC - BASE_ADDRESS) / 4 ;
                //sp_IR = instr[n];
                
                cout << "Instruction in IR is :" << str[n] << endl;
                cout << "Current instruction address is " << hex << sp_PC << endl;
                sp_NPC = sp_PC + 0x04;
                
                IF_ID.

                if (instr[n].opcode != EOP)
                {
                        exec_state = decode;
                        current_status.s = in_progress;
                        number_of_cycles ++;
                        clock_cycles++;
                        cout << "clock cycles after reset:" << dec << clock_cycles << endl;
                        break;
                        
                }
                else
                {
                    
                    current_status.s = terminated;
                    break;
                }
                
                 
            }
            else
            {
               number_of_cycles = 0;
               current_status.s = terminated;
               break;
            }
            
            
        }
        
        case decode :
        {
            cout << "decoding Instruction ..\n";
           if ( (number_of_cycles != c) || (c==0) )
           {
                        if ( (instr[n].opcode == ADD) || (instr[n].opcode == SUB) || (instr[n].opcode == XOR) )
                        {
                            sp_A = regs[instr[n].source_1_index];
                            sp_B = regs[instr[n].source_2_index];

                        }
                        else if ( ( instr[n].opcode == ADDI) || (instr[n].opcode == SUBI))
                        {
                            sp_A = regs[instr[n].source_1_index];
                            value = (0x0000FFFF & instr[n].imm);
                            mask = 0x000080000;
                            if (mask & instr[n].imm)
                                value = value + 0xFFFF0000;
                            sp_IMM = value;

                        }
                        else if (instr[n].opcode == LW) 
                        {
                            sp_A = instr[n].base_reg_index ;
                            sp_IMM = instr[n].offset;


                        }
                        else if (instr[n].opcode == SW)
                        {
                            sp_B = regs[instr[n].source_1_index];
                            sp_A = regs[instr[n].base_reg_index];
                            sp_IMM = instr[n].offset;
                            cout << "B holds :" << hex << sp_B << endl;
                            cout << "A holds" << hex << sp_A << endl;
                            cout << "IMM holds" << hex << sp_IMM << endl;
                        }
                        
                        
                exec_state = execute;
                current_status.s = in_progress;
                number_of_cycles ++;
                clock_cycles++;
                cout << "clock cycles :" << dec << clock_cycles << endl;
                break;
           }
           else
           {
               number_of_cycles = 0;
               current_status.s = terminated;
               break;
           }
            
            
        }
        
        case execute :
        {
            
            cout << "Executing Instruction..\n";
              if ( (number_of_cycles != c) || (c==0) )
              {
                                // Calculate Effective Address for memory instructions
                                if ( (instr[n].opcode == LW) || (instr[n].opcode == SW) )
                                {
                                    sp_ALU_OUTPUT = sp_A + sp_IMM;
                                    cout << "Memory address referred :" << hex << sp_ALU_OUTPUT << endl;

                                }
                                else if ((instr[n].opcode == ADD) )
                                {
                                    sp_ALU_OUTPUT = sp_A + sp_B;
                                }
                                 else if ((instr[n].opcode == SUB) )
                                {
                                    sp_ALU_OUTPUT = sp_A - sp_B;
                                }
                                 else if ((instr[n].opcode == XOR) )
                                {
                                    sp_ALU_OUTPUT = sp_A ^ sp_B;
                                }
                                 else if ( (instr[n].opcode == ADDI) )
                                {
                                    sp_ALU_OUTPUT = sp_A + sp_IMM;
                                }
                                else if ( (instr[n].opcode == SUBI) )
                                {
                                    sp_ALU_OUTPUT = sp_A - sp_IMM;
                                }
                                else if ( (instr[n].opcode == BLTZ) )
                                {
                                    
                                    sp_ALU_OUTPUT = k.find_elt(instr[n].label);
                                   // sp_ALU_OUTPUT = sp_NPC + (sp_IMM << 2);
                                    sp_COND = ( regs[instr[n].source_1_index] < 0 );
                                    //cout << "Branch taken or not :"<< sp_COND << endl;
                                    //cout << "If yes, the target address is :" << sp_ALU_OUTPUT << endl;

                                }
                                else if ( (instr[n].opcode == BNEZ) )
                                {
                                    
                                   
                                    sp_ALU_OUTPUT = k.find_elt(instr[n].label);
                                    //sp_ALU_OUTPUT = sp_NPC + (sp_IMM << 2);
                                    sp_COND = ( regs[instr[n].source_1_index] != 0 );
                                    //cout << "Branch taken or not :"<< sp_COND << endl;
                                    //cout << "If yes, the target address is :" << sp_ALU_OUTPUT << endl;

                                }
                                
                                
                                 exec_state = mem_access;
                                 current_status.s = in_progress;
                                 number_of_cycles ++;
                                 clock_cycles++;
                                 cout << "clock cycles :" << dec << clock_cycles << endl;
                                 break;
              }
              else
              {
                number_of_cycles = 0;
                current_status.s = terminated;
                break; 
              }

        }

        case mem_access :
        {
            cout << "Memory access stage reached..\n";
                 if ( (number_of_cycles != c) || (c==0) )
                 {
                                // Update PC for all instructions 
                                sp_PC = sp_NPC;
                                sp_NPC = sp_PC + 0x04;
                                // for loads
                                if (instr[n].opcode == LW)
                                {
                                    sp_LMD = data_memory[sp_ALU_OUTPUT];

                                }

                                // For Stores
                                else if (instr[n].opcode == SW)
                                {
                                    cout << hex << sp_B << endl;
                                    cout << hex << sp_ALU_OUTPUT << endl;
                                     data_memory[sp_ALU_OUTPUT] = sp_B >> 0;
                                     data_memory[sp_ALU_OUTPUT + 1] = sp_B >> 8;
                                     data_memory[sp_ALU_OUTPUT + 2] = sp_B >> 16;
                                     data_memory[sp_ALU_OUTPUT + 3] = sp_B >> 24;
                                       

                                }
                                else if (instr[n].opcode == BLTZ)
                                {
                                    if (sp_COND)
                                    {
                                        sp_PC = sp_ALU_OUTPUT;
                                        
                                    }
                                }
                                else if (instr[n].opcode == BNEZ)
                                {
                                    if (sp_COND)
                                    {
                                        sp_PC = sp_ALU_OUTPUT;
                                       
                                    }
                                        
                                }
                                
                                    if ( (instr[n].opcode == BNEZ) || (instr[n].opcode == BLTZ) )
                                    {
                                        exec_state = write_back;
                                        current_status.s = in_progress;
                                        
                                    }
                                    else
                                    {
                                        exec_state = write_back;
                                        current_status.s = in_progress;
                                    }
                                
                                        
                                 number_of_cycles ++;
                                
                                 clock_cycles++;
                                 cout << "clock cycles :" << dec <<  clock_cycles << endl;
                                 break;
                 }
                 else
                 {
                    number_of_cycles = 0;
                    current_status.s = terminated;
                    break; 
                 }
        
        }
                            
                            
                            
        
        case write_back :
        {
            
            cout << "Write back to registers..\n";
             if ( (number_of_cycles != c) || (c==0) )
             {
            
                        if ( (instr[n].opcode == ADD) || (instr[n].opcode == SUB) || (instr[n].opcode == XOR) )
                        {
                            regs[instr[n].destination_index] = sp_ALU_OUTPUT;

                        }
                        else if (( instr[n].opcode == ADDI) || (instr[n].opcode == SUBI ))
                        {
                            regs[instr[n].destination_index] = sp_ALU_OUTPUT;
                        }
                        else if (instr[n].opcode == LW)
                        {
                            regs[instr[n].destination_index] = sp_LMD;
                        }
                        
                                 exec_state = fetch;
                                 current_status.s = in_progress;
                                 number_of_cycles ++;
                                 clock_cycles++;
                                 //num_instructions++;
                                 cout << "clock cycles :" << dec << clock_cycles << endl;
                                 //if( (instr[n].opcode != BLTZ) || (instr[n].opcode != BNEZ))
                                 //{
                                        num_instructions++;
                                        cout << "number of instructions executed:" << num_instructions << endl;
                                        break;
                                // }
                        
             }
             else
             {
                    number_of_cycles = 0;
                    current_status.s = terminated;
                    break; 
                 
             }
                        
                        
        }
        
        default:
        {
                   
        }
    }
    
  return current_status;  
}
