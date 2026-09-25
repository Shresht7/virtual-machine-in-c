# Virtual Machine in C

A simple stack-based virtual machine implemented in C.

## Registers

6 general-purpose registers `A`, `B`, `C`, `D`, `E`, `F`

## Stack

The virtual machine uses a stack to store temporary values. The stack supports basic operations like `push` and `pop`.

## Instructions

| Code | Instruction              | Description                                   |
| ---- | ------------------------ | --------------------------------------------- |
| `0`  | `PSH <value>`            | Push a value onto the _[stack]_.              |
| `1`  | `POP`                    | Pop a value from the _[stack]_.               |
| `2`  | `SET <register> <value>` | Set the value of a _[register]_.              |
| `3`  | `ADD`                    | Add the top two values on the _[stack]_.      |
| `4`  | `SUB`                    | Subtract the top two values on the _[stack]_. |
| `5`  | `MUL`                    | Multiply the top two values on the _[stack]_. |
| `6`  | `DIV`                    | Divide the top two values on the _[stack]_.   |
| `7`  | `STP`                    | Stop the execution of the _[program]_.        |

## Program

Read only sequence of _[instructions]_.

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


## Program Counter or Instruction Pointer

The **program counter** (or **instruction pointer**) keeps track of the current _[instruction]_ being executed by the virtual machine. It is automatically incremented after each instruction is executed.

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

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

[stack]: #stack
[register]: #registers
[program]: #program
[instructions]: #instructions
