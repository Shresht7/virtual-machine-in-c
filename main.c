// Library
#include <stdio.h>

// The set of all instructions of the virtual machine
typedef enum
{
    PSH,
    POP,
    SET,
    ADD,
    STP,
} InstructionSet;

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

int main(void)
{
    printf("Hello, Virtual Machine!\n");
    return 0;
}
