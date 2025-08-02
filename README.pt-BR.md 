[← Voltar ao índice](README.md)

# BCPU-2

A **BCPU-2** (Basic Central Processing Unit 2) é uma CPU didática de 4 bits, com **16 opcodes** e **dois acumuladores** (RA e RB). Foi criada para fins educacionais e de portfólio.

#### Caso queira saber do **Assembler da BCPU-2**, clique _[Aqui](#Assembler)_.

---

## Arquitetura

- **Largura de palavra:** 4 bits
- **Memória de programa (ROM):** 16 × 4 bits
- **Memória de dados (RAM):** 16 × 4 bits

---

## Registradores

| Nome   | Bits | Função                                                                                                                          |
|:------:|:----:|:--------------------------------------------------------------------------------------------------------------------------------|
| **IR** | 4    | Registrador de Instrução: captura o opcode de 4 bits (e armazena o nibble de argumento) lido da ROM antes da decodificação.    |
| **RA** | 4    | **Acumulador Primário**: primeiro operando da ALU e destino da maioria das operações; pode carregar da/gravar na RAM e ser exibido com `SHOW RA`. |
| **RB** | 4    | **Acumulador Secundário**: segundo operando da ALU, frequentemente usado para preservar valores entre instruções; também pode ser exibido com `SHOW RB`.   |

---

## Tabela de Instruções (Opcodes)

Cada instrução ocupa 1 nibble (4 bits) de opcode mais 1 nibble de argumento (quando aplicável).

| Opcode | Mnemonic                  | Descrição                                        |
|:------:|:--------------------------|:-------------------------------------------------|
| `0x0`  | `NOP`                     | Não faz nada.                                    |
| `0x1 a`| `SET RA, a`               | RA ← RAM[a]                                      |
| `0x2 a`| `SET RB, a`               | RB ← RAM[a]                                      |
| `0x3 0`| `MOV RA → RB`             | RB ← RA                                          |
| `0x4 0`| `MOV RB → RA`             | RA ← RB                                          |
| `0x5 a`| `MOV RA → RAM[a]`         | RAM[a] ← RA                                      |
| `0x6 a`| `MOV RAM[a] → RA`         | RA ← RAM[a]                                      |
| `0x7 a`| `MOV RB → RAM[a]`         | RAM[a] ← RB                                      |
| `0x8 a`| `MOV RAM[a] → RB`         | RB ← RAM[a]                                      |
| `0x9 a`| `ADD RA, RB → RAM[a]`     | RAM[a] ← (RA + RB) mod 16                        |
| `0xA a`| `SUB RA, RB → RAM[a]`     | RAM[a] ← (RA – RB) mod 16                        |
| `0xB a`| `JMP a`                   | Salto incondicional para endereço `a`.           |
| `0xC 0`| `SHOW RA`                 | Exibe o valor de RA no display/saída.            |
| `0xD 0`| `SHOW RB`                 | Exibe o valor de RB no display/saída.            |
| `0xE a`| `SHOW RAM[a]`             | Exibe RAM[a] no display/saída.                   |
| `0xF 0`| `HALT`                    | Encerra a execução.                              |

---

## Abrindo no Logisim

1. [Instale](https://github.com/logisim-evolution/logisim-evolution) ou abra o **Logisim** (recomenda-se a versão 3.9.0 ou superior).

2. Carregue o arquivo **`cpu/CPU.circ`**.

3. Pressione no **Power-On Reset**, Limpe a ROM e RAM (Botão direito -> Limpar conteúdos), ajuste a frequencia de clock (Simular -> Frequencia de pulso -> Recomendado **8Hz**).

4. Carregue o programa `.hex` na ROM (Botão direito -> Carregar imagem...) e inicie o clock (Control + K)

5. Observe os displays de **RA**, **RB** e **saída da RAM** conforme seu programa roda.

---

## Assembler

### UNIX / Linux / macOS:

1. Execute no diretório principal o arquivo `build.sh`
> **Certifique-se de que tenha instalado C++20 e Cmake**

2. Para executa-lo, basta ir na pasta `build/` e executar `bcpu-asm` desse jeito:
   ```bash
     ./bcpu-asm exemplo.asm exemplo.hex

