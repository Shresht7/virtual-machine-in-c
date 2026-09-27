// Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define MAX_PROGRAM_SIZE 1024 // Maximum size of the program that can be loaded into memory

// The program to be executed by the virtual machine
// It is simply a sequence of instructions and their operands.
// Each instruction is represented by an integer corresponding to the InstructionSet enum
// and as such is simply an array of integers. e.g. 0 3 0 4 3 2 4
int program[MAX_PROGRAM_SIZE] = {
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

// The total length of the program
int program_length = sizeof(program) / sizeof(program[0]);

// VM STATE
// --------

// Flag to indicate if the virtual machine is running
int RUNNING = 1;

// REGISTERS
// ---------

// The set of all general-purpose registers in the virtual machine
typedef enum
{
    // GENERAL PURPOSE REGISTERS

    A, // General-purpose register A
    B, // General-purpose register B
    C, // General-purpose register C
    D, // General-purpose register D
    E, // General-purpose register E
    F, // General-purpose register F

    NUM_GENERAL_REGISTERS, // Total number of general-purpose registers

    // SPECIAL PURPOSE REGISTERS

    IP, // Instruction pointer register
    SP, // Stack pointer register

    NUM_REGISTERS // Total number of registers

} RegisterSet;

// Array to hold the values of the general-purpose registers
int REGISTER[NUM_REGISTERS] = {0};

// STACK
// -----

#define STACK_SIZE 256 // Maximum size of the stack used by the virtual machine
int STACK[STACK_SIZE]; // The stack used by the virtual machine to store values

// Push a value onto the stack
void push(int value)
{
    if (REGISTER[SP] >= STACK_SIZE - 1)
    {
        printf("Stack overflow!\n");
        return;
    }
    STACK[++REGISTER[SP]] = value; // Push the value onto the stack and only then increment the stack pointer
}
// Pop a value from the stack, and return it
int pop()
{
    if (REGISTER[SP] < 0)
    {
        printf("Stack underflow!\n");
        return -1; // Return an error value indicating stack underflow
    }
    return STACK[REGISTER[SP]--]; // Pop the value from the stack and then decrement the stack pointer
}

// Helper function to verify that the stack holds at least `count` values before an instruction consumes them
int require(int count)
{
    if (REGISTER[SP] < count - 1)
    {
        printf("Stack Underflow!\n");
        RUNNING = 0; // Stop the execution instead of computing with garbage
        return 0;
    }
    return 1;
}

// FETCH
// -----

// Read the word at `index`, halting the VM if it is out of bounds
int read(int index)
{
    if (index < 0 || index >= program_length)
    {
        printf("Out-of-bounds read at %d\n", index);
        RUNNING = 0;
        return 0;
    }
    return program[index]; // Return the value at the specified index if it is within bounds
}

// Fetch the current instruction pointed to by the instruction pointer (ip) from the program array
int fetch()
{
    return read(REGISTER[IP]);
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
        value = read(++REGISTER[IP]); // Fetch the value to push from the next instruction in the program array
        push(value);
        break;

    // POP: Pop the top value from the stack and print it
    case POP:
        if (!require(1))
            break;             // Stop execution if there are not enough values on the stack
        value = pop();         // Pop the top value from the stack
        printf("%d\n", value); // Print the popped value
        break;

    // SET: Set the value of a register
    case SET:
    {
        int reg = read(++REGISTER[IP]); // Fetch the register index from the next instruction in the program array
        value = read(++REGISTER[IP]);   // Fetch the value to set from the next instruction in the program array
        if (reg >= 0 && reg < NUM_GENERAL_REGISTERS)
        {
            REGISTER[reg] = value; // Set the value of the specified register
        }
        else
        {
            printf("Invalid register index!\n");
        }
    }
    break;

    // ADD: Pop the top two values from the stack, add them, and push the result back onto the stack
    case ADD:
        if (!require(2))
            break;
        {
            int a = pop();   // Pop the top value from the stack
            int b = pop();   // Pop the next value from the stack
            int res = b + a; // Calculate the result of adding the two values
            push(res);       // Push the result back onto the stack
        }
        break;

    // SUB: Pop the top two values from the stack, subtract the second from the first, and push the result back onto the stack
    case SUB:
        if (!require(2))
            break;
        {
            int a = pop();   // Pop the top value from the stack
            int b = pop();   // Pop the next value from the stack
            int res = b - a; // Calculate the result of subtracting the two values
            push(res);       // Push the result back onto the stack
        }
        break;

    // MUL: Pop the top two values from the stack, multiply them, and push the result back onto the stack
    case MUL:
        if (!require(2))
            break;
        {
            int a = pop();   // Pop the top value from the stack
            int b = pop();   // Pop the next value from the stack
            int res = b * a; // Calculate the result of multiplying the two values
            push(res);       // Push the result back onto the stack
        }
        break;

    // DIV: Pop the top two values from the stack, divide the second by the first, and push the result back onto the stack
    case DIV:
        if (!require(2))
            break;
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

// ---
// RUN
// ---

// The main function of the virtual machine. It initializes the running flag and enters the main execution loop
int run()
{
    REGISTER[SP] = -1; // Initialize the stack pointer register to -1 indicating an empty stack
    REGISTER[IP] = 0;  // Initialize the instruction pointer register to 0 indicating the start of the program

    // Main execution loop of the virtual machine
    while (RUNNING)
    {
        int instruction = fetch(); // Fetch the current instruction from the program array
        execute(instruction);      // Execute the fetched instruction
        REGISTER[IP]++;            // Increment the instruction pointer to point to the next instruction in the program array
    }

    return 0; // Return 0 to indicate successful execution of the program
}

// ====
// MAIN
// ====

// loads the `.chasm` assembly file, translates it into machine code, and stores it into memory for execution
void load_program(const char *filename)
{
    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    int p = 0; // The program cursor index

    char word[16]; // Buffer to store the current word being processed
    int w = 0;     // Index within the current word buffer
    char c = 0;    // Variable to store the current character being read from the file
    while ((c = fgetc(file)) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            word[w] = '\0'; // Null-terminate the current word

            int instruction = -1;
            if (strncmp(word, "PSH", 3) == 0)
            {
                instruction = PSH;
            }
            else if (strncmp(word, "POP", 3) == 0)
            {
                instruction = POP;
            }
            else if (strncmp(word, "ADD", 3) == 0)
            {
                instruction = ADD;
            }
            else if (strncmp(word, "SUB", 3) == 0)
            {
                instruction = SUB;
            }
            else if (strncmp(word, "MUL", 3) == 0)
            {
                instruction = MUL;
            }
            else if (strncmp(word, "DIV", 3) == 0)
            {
                instruction = DIV;
            }
            else if (strncmp(word, "SET", 3) == 0)
            {
                instruction = SET;
            }
            else if (strncmp(word, "STP", 3) == 0)
            {
                instruction = STP;
            }

            if (instruction != -1)
            {
                program[p++] = instruction; // Store the instruction in the program array and move the program cursor to the next position
            }
            else
            {
                int number = atoi(word); // Convert the current word to an number
                program[p++] = number;   // Store the converted number in the program array, and move the program cursor to the next position
            }

            w = 0; // Reset the word index for the next word
        }
        else
        {
            word[w++] = c; // Store the current character in the word buffer and increment the word index
        }
    }

    // Handle the last word in the file if it wasn't followed by a whitespace character
    if (w > 0)
    {
        word[w] = '\0';          // Null-terminate the last word
        int number = atoi(word); // Convert the last word to a number
        program[p++] = number;   // Store the converted number in the program array
    }

    program_length = p; // Store the length of the program in the program_length variable

    fclose(file);
}

// The main entrypoint of the program
int main(int argc, char *argv[])
{
    // If a program file is provided as a command-line argument...
    if (argc > 1)
    {
        load_program(argv[1]); // Load the program file into the virtual machine's memory
    }

    return run();
}
