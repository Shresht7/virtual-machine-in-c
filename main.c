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

int main(void)
{
    printf("Hello, Virtual Machine!\n");
    return 0;
}
