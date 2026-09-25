// Library
#include <stdio.h>

// INSTRUCTION SET
// ---------------

// The set of all instructions of the virtual machine
typedef enum
{
    PSH,
    POP,
    SET,
    ADD,
    STP,
} InstructionSet;

// PROGRAM
// -------

// The program to be executed by the virtual machine
// It is simply a sequence of instructions and their operands.
// Each instruction is represented by an integer corresponding to the InstructionSet enum
// and as such is simply an array of integers. e.g. 0 3 0 4 3 2 4
const int program[] = {
    // Push 3 onto the stack
    PSH,
    3,
    // Push 4 onto the stack
    PSH,
    4,
    // Add the top two values on the stack and push the result back onto the stack
    ADD,
    // Pop the top value from the stack. (and print it)
    POP,
    // Stop the execution of the program
    STP,
};

// The instruction pointer (or program counter) keeps track of the current instruction being executed by the virtual machine.
// Simply serves as the index in the program array as to which instruction is currently being executed.
int ip = 0;

// VM STATE
// --------

// Flag to indicate if the virtual machine is running
int RUNNING = 1;

// FETCH
// -----

// Fetch the current instruction pointed to by the instruction pointer (ip) from the program array
int fetch()
{
    return program[ip];
}

// EXECUTE
// -------

// Execute the given instruction by the virtual machine.
void execute(int instruction)
{
    // Execute the instruction based on its type
    switch (instruction)
    {
    // FIX: Will consider 4 as STP and stop the execution of the virtual machine!
    case STP:
        RUNNING = 0; // Stop the execution of the virtual machine
        break;

    default:
        printf("Unknown instruction: %d\n", instruction);
        // running = 0; // Stop the execution of the virtual machine on unknown instruction
        break;
    }
}

// ====
// MAIN
// ====

// The main function of the virtual machine. It initializes the running flag and enters the main execution loop.
int main(void)
{
    // Main execution loop of the virtual machine
    while (RUNNING)
    {
        int instruction = fetch(); // Fetch the current instruction from the program array
        execute(instruction);      // Execute the fetched instruction
        ip++;                      // Increment the instruction pointer to point to the next instruction in the program array
    }

    return 0; // Return 0 to indicate successful execution of the program
}
