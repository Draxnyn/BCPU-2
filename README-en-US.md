[← Back to index](README.md)

# BCPU-2

**BCPU-2** (Basic Central Processing Unit 2) is a didactic 4-bit CPU with **16 opcodes** and **two accumulators** (RA and RB). Designed for educational purposes and as a portfolio project.

#### If you want to learn about the **BCPU-2 Assembler**, click _[Here](#Assembler)_.

---

## Architecture

- **Word size:** 4 bits  
- **Program memory (ROM):** 16 × 4 bits  
- **Data memory (RAM):** 16 × 4 bits  

---

## Registers

| Name | Bits | Function                                                                                                                        |
|:----:|:----:|:-------------------------------------------------------------------------------------------------------------------------------|
| **IR** | 4  | Instruction Register: captures the 4-bit opcode (and latches the argument nibble) fetched from ROM before decoding.             |
| **RA** | 4  | **Primary Accumulator:** first ALU operand and destination for most operations; can load from/store to RAM and be displayed with `SHOW RA`. |
| **RB** | 4  | **Secondary Accumulator:** second ALU operand, often used to preserve values across instructions; also can be displayed with `SHOW RB`.    |

---

## Instruction Set (Opcodes)

Each instruction occupies 1 nibble (4 bits) of opcode plus 1 nibble of argument (when applicable).

| Opcode  | Assembly          | Mnemonic               | Description                                          |
|:-------:|:-----------------:|:-----------------------|:-----------------------------------------------------|
| `0x0`   | `null`            | `NOP`                  | No operation.                                        |
| `0x1 a` | `set RA, a`       | `SET RA, a`            | RA ← RAM[a]                                          |
| `0x2 a` | `set RB, a`       | `SET RB, a`            | RB ← RAM[a]                                          |
| `0x3 0` | `mov RA, RB`      | `MOV RA → RB`          | RB ← RA                                              |
| `0x4 0` | `mov RB, RA`      | `MOV RB → RA`          | RA ← RB                                              |
| `0x5 a` | `mov RA, RAM[a]`  | `MOV RA → RAM[a]`      | RAM[a] ← RA                                          |
| `0x6 a` | `mov RAM[a], RA`  | `MOV RAM[a] → RA`      | RA ← RAM[a]                                          |
| `0x7 a` | `mov RB, RAM[a]`  | `MOV RB → RAM[a]`      | RAM[a] ← RB                                          |
| `0x8 a` | `mov RAM[a], RB`  | `MOV RAM[a] → RB`      | RB ← RAM[a]                                          |
| `0x9 a` | `add RAM[a]`      | `ADD RA, RB → RAM[a]`  | RAM[a] ← (RA + RB) mod 16                            |
| `0xA a` | `sub RAM[a]`      | `SUB RA, RB → RAM[a]`  | RAM[a] ← (RA – RB) mod 16                            |
| `0xB a` | ``jump a`` / ``jump @a`` | `JMP a`                | Unconditional jump to address **or** cicle `a`.                   |
| `0xC 0` | `show RA`         | `SHOW RA`              | Display the value of RA on the display/output.       |
| `0xD 0` | `show RB`         | `SHOW RB`              | Display the value of RB on the display/output.       |
| `0xE a` | `show RAM[a]`     | `SHOW RAM[a]`          | Display the value of RAM[a] on the display/output.   |
| `0xF 0` | `halt`            | `HALT`                 | Halt execution.                                      |

**You can use "#" for comments in the `.asm` file**

---

## Running in Logisim

1. [Install](https://github.com/logisim-evolution/logisim-evolution) or open **Logisim** (version 3.9.0 or later).  
2. Load the **`cpu/CPU.circ`** file.  
3. Press **Power-On Reset**, clear ROM and RAM (right-click → “Clear Contents”), and adjust the clock frequency (Simulate → Tick Frequency -> Recommended **8Hz**).  
4. Load your `.hex` program into ROM (right-click → “Load Image…”) and start the clock (Ctrl + K).  
5. Observe the **RA**, **RB** and **RAM** output displays as your program runs.

---

## Assembler

### UNIX / Linux / macOS

1. Run the `build.sh` file in the main directory.
> **Make sure you have C++20 and CMake installed.**

1. To run it, go into the build/ folder and execute bcpu-asm like this:
   ```bash
   ./bcpu-asm example.asm example.hex
   ```
   **Or you can use the .hex example file to load it directly into the ROM.**
   ./bcpu-asm example.asm example.hex

