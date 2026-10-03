# Encoding and Decoding DNA String Program

This project implements a simple compression and decompression program for DNA sequences using a **2-bit encoding scheme**.

Each DNA nucleotide (`A`, `T`, `C`, or `G`) is represented using two binary bits. Four DNA characters therefore fit into a single 8-bit group. The program can convert a DNA sequence into decimal values and reconstruct the original DNA sequence from those values.

## Overview

The project provides two primary operations:

* **Compression (`-c`)** — Converts a DNA sequence into a compact decimal representation.
* **Decompression (`-d`)** — Converts the compressed decimal representation back into a DNA sequence.

The program uses the following 2-bit encoding:

| DNA Character | Binary |
| ------------- | ------ |
| `A`           | `00`   |
| `T`           | `01`   |
| `C`           | `10`   |
| `G`           | `11`   |

Because each DNA character requires only two bits, **four characters can be stored in one 8-bit value**.

For example:

```text
ATTC
```

is encoded as:

```text
A  T  T  C
00 01 01 10
```

which produces:

```text
00010110
```

The binary value `00010110` corresponds to decimal `22`.

## Project Structure

```text
.
├── proj1.c
├── compress.c
├── compress.h
├── decompress.c
├── decompress.h
└── Makefile
```

### `compress.c`

Contains the DNA compression implementation.

The main function is:

```c
void compress(int len, char str[])
```

It:

1. Determines the required binary-string length.
2. Converts each DNA character into two bits.
3. Adds trailing zero bits when the DNA sequence length is not a multiple of four.
4. Groups the binary sequence into 8-bit sections.
5. Converts each 8-bit section into a decimal integer.
6. Prints the original sequence length followed by the decimal values.

### `decompress.c`

Contains the DNA decompression implementation.

The main function is:

```c
void decompress(int remainingChar, char str[])
```

It:

1. Converts a decimal value into an 8-bit binary string.
2. Reads the binary string two bits at a time.
3. Converts each 2-bit pair back into a DNA character.
4. Prints the reconstructed DNA sequence.

### `proj1.c`

Provides the main program and command-line interface. The source files provided here reference `proj1.c`, although its implementation is not included in the supplied code.

### `Makefile`

Automates compilation, linking, running, and cleaning the project.

## DNA Encoding

The compression scheme uses two bits for each DNA character:

```text
A → 00
T → 01
C → 10
G → 11
```

This mapping allows DNA sequences to be represented efficiently because there are only four possible nucleotide characters.

### Example

Consider:

```text
ATTCGG
```

The characters are converted individually:

```text
A → 00
T → 01
T → 01
C → 10
G → 11
G → 11
```

The resulting binary sequence is:

```text
000101101111
```

Since the sequence contains six characters, it requires:

```text
6 × 2 = 12 bits
```

The implementation pads the sequence to a multiple of four characters, resulting in:

```text
16 bits
```

The padded binary sequence is:

```text
0001011011110000
```

This is divided into two 8-bit groups:

```text
00010110
11110000
```

which correspond to decimal values:

```text
22
240
```

The compressed representation therefore begins with the original length:

```text
6 22 240
```

The original length is important because the final 8-bit group may contain padding zeros.

## Compression

The compression operation is performed with:

```bash
./proj1.out -c ATTCGG
```

The program converts the DNA sequence into its binary representation and then converts each 8-bit group into a decimal value.

The output format is:

```text
<original length> <decimal value> <decimal value> ...
```

For example:

```text
6 22 240
```

The first number indicates that the original DNA sequence contained six characters.

The remaining numbers represent the encoded 8-bit groups.

## How Compression Works

The `compress()` function first calculates the required binary length.

If the DNA sequence length is divisible by four:

```c
biStrLen = len * 2;
```

Otherwise, the length is rounded up to the next multiple of four characters before multiplying by two.

For every DNA character, two bits are generated:

```c
if (str[i] == 'T') {
    biStr[i * 2] = '0';
    biStr[i * 2 + 1] = '1';
}
```

Similarly:

```text
A → 00
T → 01
C → 10
G → 11
```

If the sequence does not fill the final four-character group, the remaining positions are padded with:

```text
00
```

which corresponds to `A` under the encoding scheme.

## Converting Binary to Decimal

The `baseTen()` function processes the binary string eight bits at a time.

```c
sum = (sum << 1) | (biStr[index] - '0');
```

The left shift moves the current value one binary position to the left, effectively multiplying it by two. The OR operation then adds the next binary bit.

For example:

```text
00010110
```

becomes:

```text
22
```

The function prints the original DNA length first and then each decimal representation.

## Decompression

The decompression operation is performed with:

```bash
./proj1.out -d 3 132
```

The decompression function receives the number of characters that should be reconstructed and the decimal value represented as a string.

The decimal value is converted back into an 8-bit binary representation.

For example:

```text
132
```

is represented as:

```text
10000100
```

The binary string is then processed two bits at a time:

```text
10 00 01 00
```

Using the encoding table:

```text
10 → C
00 → A
01 → T
00 → A
```

the reconstructed sequence is:

```text
CATA
```

The `remainingChar` parameter determines how many two-bit groups are converted. This prevents padded bits from being interpreted as additional DNA characters.

## Binary Conversion

The decompression function uses repeated division by two through bit shifting:

```c
quotient = quotient >> 1;
```

The remainder determines each binary digit:

```c
biStr[i] = quotient % 2 + '0';
```

The result is an 8-character binary string:

```text
00000000
```

through:

```text
11111111
```

depending on the decimal input.

## Decoding DNA Characters

During decompression, every two bits are interpreted using the same mapping used during compression:

```text
00 → A
01 → T
10 → C
11 → G
```

The implementation checks each pair:

```c
if (biStr[i * 2] == '0' && biStr[i * 2 + 1] == '0') {
    printf("%s", "A");
}
```

The remaining combinations produce `T`, `C`, or `G`.

## Makefile

The project includes a Makefile that automates compilation.

The compiler is defined as:

```make
CC = gcc
```

Debugging information is enabled using:

```make
DEBUG = -g
```

Compiler flags include:

```make
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
```

## Building the Project

The default compilation target is:

```bash
make
```

This builds:

```text
proj1.out
```

The executable is linked from:

```text
proj1.o
compress.o
decompress.o
```

The Makefile also provides an explicit `compile` target:

```bash
make compile
```

## Running the Example

The Makefile provides a `run` target:

```bash
make run
```

which executes:

```bash
./proj1.out -c ATTCGG
./proj1.out -d 3 132
```

This provides examples of both compression and decompression.

## Cleaning the Project

To remove the compiled object files and executable:

```bash
make clean
```

The Makefile removes:

```text
*.o
proj1.out
```

## Complete Workflow

The overall compression workflow is:

```text
DNA Sequence
     │
     ▼
Convert each character to 2 bits
     │
     ▼
Create binary sequence
     │
     ▼
Pad to multiple of 8 bits
     │
     ▼
Split into 8-bit groups
     │
     ▼
Convert binary groups to decimal
     │
     ▼
Compressed Representation
```

The decompression workflow reverses this process:

```text
Compressed Decimal Values
          │
          ▼
Convert decimal values to 8-bit binary
          │
          ▼
Split into 2-bit groups
          │
          ▼
Convert each pair to DNA character
          │
          ▼
Use original length to remove padding
          │
          ▼
Original DNA Sequence
```

## Key Concepts Demonstrated

This project demonstrates several fundamental C programming and computer science concepts:

* C functions
* Arrays and character strings
* Command-line arguments
* File organization using header files
* Bit shifting
* Binary representation
* Decimal-to-binary conversion
* Binary-to-decimal conversion
* String manipulation
* Dynamic calculation of array sizes
* Makefiles
* GCC compilation
* Data compression using a fixed-size encoding scheme

## Quick Start

Build the project:

```bash
make
```

Run the provided examples:

```bash
make run
```

Clean compiled files:

```bash
make clean
```

Or run the executable directly:

```bash
./proj1.out -c ATTCGG
./proj1.out -d 3 132
```

## Summary

This project implements a compact DNA encoding system based on the observation that DNA sequences contain only four possible characters: `A`, `T`, `C`, and `G`. Each character is therefore represented using two bits.

The compression process converts DNA characters into binary, groups the bits into 8-bit values, and outputs those values as decimal integers. The decompression process converts the decimal values back into binary and then reconstructs the DNA sequence using the original sequence length to ignore padding.

The project provides practical experience with **binary data representation, bit manipulation, C programming, modular compilation, and basic data compression techniques**.
