# Virtual Machine in C

A simple stack-based virtual machine implemented in C.

## Registers

6 general-purpose registers `A`, `B`, `C`, `D`, `E`, `F`

## Program

Read only sequence of [_instructions_]

## Instructions

- `PSH <value>`: Push a value onto the stack.
- `POP`: Pop a value from the stack.
- `SET <register> <value>`: Set the value of a register.
- `ADD`: Add the top two values on the stack..
- `STP`: Stop the execution of the program.

---

## Development

```c
gcc -Wall -Wextra -Wpedantic main.c -o vm
```

---

## Reference

- [Virtual Machine in C](https://web.archive.org/web/20200121100942/https://blog.felixangell.com/virtual-machine-in-c/)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
