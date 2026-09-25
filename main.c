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

// STACK
// -----

#define STACK_SIZE 256 // Maximum size of the stack used by the virtual machine
int stack[STACK_SIZE]; // The stack used by the virtual machine to store values
int sp = -1;           // Stack pointer. initialized to -1 indicating an empty stack

// Push a value onto the stack
void push(int value)
{
    if (sp >= STACK_SIZE - 1)
    {
        printf("Stack overflow!\n");
        return;
    }
    stack[++sp] = value; // Push the value onto the stack and only then increment the stack pointer
}
// Pop a value from the stack, and return it
int pop()
{
    if (sp < 0)
    {
        printf("Stack underflow!\n");
        return -1; // Return an error value indicating stack underflow
    }
    return stack[sp--]; // Pop the value from the stack and then decrement the stack pointer
}

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
    // PUSH: Push a value onto the stack
    case PSH:
        ip++;                    // Move to the next instruction which should be the value to push
        int value = program[ip]; // Fetch the value to push from the next instruction in the program array
        push(value);
        break;

    // POP: Pop the top value from the stack and print it
    case POP:
        int value = pop();     // Pop the top value from the stack
        printf("%d\n", value); // Print the popped value
        break;

    // STP: Stop the execution of the virtual machine
    case STP:
        RUNNING = 0; // Stop the execution of the virtual machine
        break;

        // Unknown: Handle unknown instructions gracefully
    default:
        printf("Unknown instruction: %d\n", instruction);
        RUNNING = 0; // Stop the execution of the virtual machine
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
