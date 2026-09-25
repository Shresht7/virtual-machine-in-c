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
    SUB,
    MUL,
    DIV,
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

// REGISTERS
// ---------

// The set of all general-purpose registers in the virtual machine
typedef enum
{
    A,
    B,
    C,
    D,
    E,
    F,
    NUM_REGISTERS // Total number of general-purpose registers
} RegisterSet;

// Array to hold the values of the general-purpose registers
int registers[NUM_REGISTERS] = {0};

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
    int value; // Temporary variable to hold values for stack operations

    // Execute the instruction based on its type
    switch (instruction)
    {
    // PUSH: Push a value onto the stack
    case PSH:
        ip++;                // Move to the next instruction which should be the value to push
        value = program[ip]; // Fetch the value to push from the next instruction in the program array
        push(value);
        break;

    // POP: Pop the top value from the stack and print it
    case POP:
        value = pop();         // Pop the top value from the stack
        printf("%d\n", value); // Print the popped value
        break;

    // SET: Set the value of a register
    case SET:
        ip++; // Move to the next instruction which should be the register index
        {
            int reg = program[ip]; // Fetch the register index from the next instruction in the program array
            ip++;                  // Move to the next instruction which should be the value to set
            value = program[ip];   // Fetch the value to set from the next instruction in the program array
            if (reg >= 0 && reg < NUM_REGISTERS)
            {
                registers[reg] = value; // Set the value of the specified register
            }
            else
            {
                printf("Invalid register index!\n");
            }
        }
        break;

    // ADD: Pop the top two values from the stack, add them, and push the result back onto the stack
    case ADD:
    {
        int a = pop();   // Pop the top value from the stack
        int b = pop();   // Pop the next value from the stack
        int res = b + a; // Calculate the result of adding the two values
        push(res);       // Push the result back onto the stack
    }
    break;

    // SUB: Pop the top two values from the stack, subtract the second from the first, and push the result back onto the stack
    case SUB:
    {
        int a = pop();   // Pop the top value from the stack
        int b = pop();   // Pop the next value from the stack
        int res = b - a; // Calculate the result of subtracting the two values
        push(res);       // Push the result back onto the stack
    }
    break;

    // MUL: Pop the top two values from the stack, multiply them, and push the result back onto the stack
    case MUL:
    {
        int a = pop();   // Pop the top value from the stack
        int b = pop();   // Pop the next value from the stack
        int res = b * a; // Calculate the result of multiplying the two values
        push(res);       // Push the result back onto the stack
    }
    break;

    // DIV: Pop the top two values from the stack, divide the second by the first, and push the result back onto the stack
    case DIV:
    {
        int a = pop(); // Pop the top value from the stack
        int b = pop(); // Pop the next value from the stack
        if (a == 0)
        {
            printf("Division by zero is not defined!\n");
            push(b); // Push the second value back onto the stack
        }
        else
        {
            int res = b / a; // Calculate the result of dividing the two values
            push(res);       // Push the result back onto the stack
        }
    }
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
