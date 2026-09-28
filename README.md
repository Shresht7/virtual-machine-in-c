# Virtual Machine in C

A simple stack-based virtual machine implemented in C.

Virtual Machines are software emulations of physical computers; they mimic the behavior of the CPU, memory, and other hardware components, allowing to to perform arithmetic, logic, interact with I/O devices, and execute programs just like a physical machine would. Some VMs don't mimic any physical computer and are entirely made up! Like the Java Virtual Machine (JVM). This decouples the software from the underlying hardware allowing interpreters to run the same program on different hardware platforms seamlessly.

Virtual Machines are extremely simple in design. All they do, when given a [program], is execute the defined [instructions] sequentially and manipulate data using the hardware accordingly. The _"program"_ in this case, is essentially a bunch of numbers (e.g. `0 3 0 4 3 1 7`), called ***machine-code***.

Since real machines are built using transistors and other electronic components that operate on binary signals (either _ON_ `1` or _OFF_ `0`), numbers, and by extension the machine-code, are represented as a sequence of binary digits (bits). The idea remains the same though.

---

## Machine Code

### Instructions

An _"instruction"_ is a command that tells the machine to _"do something"_, such as "add two numbers". Since the only thing a computer understands is binary/numbers, the instruction are simply numbers called `OpCodes`.

Each `OpCode` represents one task that the machine "understands".

| OpCode | Instruction              | Description                                   |
| ------ | ------------------------ | --------------------------------------------- |
| `0`    | `PSH <value>`            | Push a value onto the _[stack]_.              |
| `1`    | `POP`                    | Pop a value from the _[stack]_.               |
| `2`    | `SET <register> <value>` | Set the value of a _[register]_.              |
| `3`    | `ADD`                    | Add the top two values on the _[stack]_.      |
| `4`    | `SUB`                    | Subtract the top two values on the _[stack]_. |
| `5`    | `MUL`                    | Multiply the top two values on the _[stack]_. |
| `6`    | `DIV`                    | Divide the top two values on the _[stack]_.   |
| `7`    | `STP`                    | Stop the execution of the _[program]_.        |

### Program

Read only sequence of _[instructions]_ like `0 3 0 4 3 1 7`. This sequence represents the machine-code for the virtual machine to execute.

Programs are often written in a human-readable language which is then translated into machine-code for the execution. This human-readable language is called ***assembly***. A separate program called an ***assembler*** is responsible for converting the assembly code into machine-code.

This project uses a custom dialect which I will call `chasm`.

```asm
PSH 3
PSH 4
ADD
POP
STP
```

To the virtual machine, this is simply an sequence of numbers.

```asm
0 3 0 4 3 1 7
```

#### Assembly

Assembly is a human-readable representation of machine-code instructions. Each assembly instruction corresponds to a specific `OpCode` and its operands. The assembler translates these assembly instructions into the corresponding machine-code that the virtual machine can execute.

> [!NOTE]
> Although the ***assembler*** and ***compiler*** sound similar  on the surface, they are **not** the same. An assembler simply translates, word-for-word, the assembly code into machine-code, replacing each assembly instruction with its corresponding binary representation.

### Program Counter or Instruction Pointer

The **program counter** (or **instruction pointer**) keeps track of the current _[instruction]_ being executed by the virtual machine. It is automatically incremented after each instruction is executed.

The pointer can be made to _"jump"_ to a different location in the _[program]_ instead of simply moving to the next instruction. This enables the implementation of control flow constructs like loops and conditional statements.

---

## Memory

### Registers

Registers are the working-memory of a machine. They are used to temporarily store data the CPU will need shortly. Instead of constantly accessing the main memory, the CPU can quickly read from and write to these registers.

### General-Purpose Registers

There are 6 general-purpose registers `A`, `B`, `C`, `D`, `E`, `F`.

### Special-Purpose Registers

- `IP`: The [instruction pointer][instruction-pointer] that keeps track of the current _[instruction]_ being executed. Starts at `0`, at the beginning of the _[program]_.
- `SP`: The [stack pointer][stack-pointer] that keeps track of the top of the _[stack]_.

### Stack

The virtual machine uses a stack to store temporary values. The stack supports basic operations like `push` and `pop`. The stack operates in a last-in, first-out (LIFO) manner. The `SP` register points to the top of the stack, and it is updated automatically when values are pushed or popped.

---

## Development

### Compile

```sh
gcc -Wall -Wextra -Wpedantic --debug main.c -o vm
```

### Debug

```sh
gdb ./vm
```

### Execute

```sh
./vm
```

---

## Reference

- [Virtual Machine in C](https://web.archive.org/web/20200121100942/https://blog.felixangell.com/virtual-machine-in-c/)
- [Write your Own Virtual Machine](https://www.jmeiners.com/lc3-vm/)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

<!-- Links -->
[stack]: #stack
[sp]: #stack-pointer
[stack-pointer]: #stack-pointer
[register]: #registers
[ip]: #program-counter-or-instruction-pointer
[instruction-pointer]: #program-counter-or-instruction-pointer
[program]: #program
[instructions]: #instructions
