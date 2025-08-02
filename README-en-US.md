[← Back to index](README.md)

# BCPU-2

**BCPU-2** (Basic Central Processing Unit 2) is a didactic 4-bit CPU with **16 opcodes** and **two accumulators** (RA and RB). It was designed for educational purposes and as a portfolio project.

---

## Architecture

- **Word size:** 4 bits
- **Program memory (ROM):** 16 × 4 bits
- **Data memory (RAM):** 16 × 4 bits

---

## Registers

| Name   | Bits | Function                                                                                                                          |
|:------:|:----:|:----------------------------------------------------------------------------------------------------------------------------------|
| **IR** | 4    | Instruction Register: captures the 4-bit opcode (and latches the argument nibble) fetched from ROM before decoding.              |
| **RA** | 4    | **Primary Accumulator**: first ALU operand and destination for most operations; can load from/store to RAM and be displayed with `SHOW RA`. |
| **RB** | 4    | **Secondary Accumulator**: second ALU operand, often used to preserve values across instructions; can also be displayed with `SHOW RB`.    |


---

## Instruction Set (Opcodes)

Each instruction uses 1 nibble (4 bits) for the opcode plus 1 nibble for its argument when applicable. Consult `cpu/opcodes.txt` for the full reference.

| Opcode | Mnemonic                  | Description                                          |
|:------:|:--------------------------|:-----------------------------------------------------|
| `0x0`  | `NOP`                     | No operation.                                        |
| `0x1 a`| `SET RA, a`               | RA ← RAM[a]                                          |
| `0x2 a`| `SET RB, a`               | RB ← RAM[a]                                          |
| `0x3 0`| `MOV RA → RB`             | RB ← RA                                              |
| `0x4 0`| `MOV RB → RA`             | RA ← RB                                              |
| `0x5 a`| `MOV RA → RAM[a]`         | RAM[a] ← RA                                          |
| `0x6 a`| `MOV RAM[a] → RA`         | RA ← RAM[a]                                          |
| `0x7 a`| `MOV RB → RAM[a]`         | RAM[a] ← RB                                          |
| `0x8 a`| `MOV RAM[a] → RB`         | RB ← RAM[a]                                          |
| `0x9 a`| `ADD RA, RB → RAM[a]`     | RAM[a] ← (RA + RB) mod 16                            |
| `0xA a`| `SUB RA, RB → RAM[a]`     | RAM[a] ← (RA – RB) mod 16                            |
| `0xB a`| `JMP a`                   | Unconditional jump to address `a`.                   |
| `0xC 0`| `SHOW RA`                 | Display the value of RA (0–15).                      |
| `0xD 0`| `SHOW RB`                 | Display the value of RB (0–15).                      |
| `0xE a`| `SHOW RAM[a]`             | Display the value of RAM[a] (0–15).                  |
| `0xF 0`| `HALT`                    | Halt execution.                                      |

---

## Running in Logisim

1. Open **Logisim** (version 3.9.0 or later is recommended).
2. Load the file `cpu/CPU.circ`.
3. Press **Power-On Reset**, clear ROM and RAM (right-click → “Clear Contents”), and adjust the clock frequency (Simulate → Tick Frequency).
4. Load your program’s `.hex` into the ROM (right-click → “Load Image…”), then start the clock (Ctrl + K).
5. Watch the RA, RB and RAM output displays as your program runs.

---
