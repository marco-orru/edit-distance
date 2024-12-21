# Edit Distance

> Part of a University project for the class _Algorithms and Data Structures_ (**[ASD](https://laurea.informatica.unito.it/do/corsi.pl/Show?_id=iw3r)**, *Algoritmi e Strutture Dati*, UNITO Informatica).

This repository implements the **Edit Distance** algorithm and uses it to detect and correct errors in a text file based on a provided dictionary. The project is written in C and includes a command-line interface for processing files.

## Features

- **Edit Distance Algorithm**: Supports both recursive and dynamic programming (memoized) implementations.
- **Text Correction**: Identifies misspelled words in a file and suggests corrections based on a dictionary.
- **Command-Line Interface**: Easy-to-use CLI for specifying input files and dictionaries.
- **Unit Tests**: Ensures reliability and correctness of the core functionalities.

---

## File Structure

### Source Code
- `source/main.c`: Entry point of the application.
- `source/library/edit-distance.c`: Implementation of the edit distance algorithm.
- `source/library/correct-file.c`: Logic for text correction using the dictionary.
- `source/library/diagnostics.h`: Utility functions for error handling and diagnostics.

### Tests
- `source/tests_main.c`: Unit tests for the edit distance and correction functionalities.

---

## How It Works

1. The **Edit Distance Algorithm** calculates the minimum number of operations (insertion, deletion, substitution) to convert one string into another.
2. The `correct_file` function:
   - Reads the dictionary file and stores it in memory.
   - Processes the input file, word by word.
   - Computes the edit distance between each word in the input file and all words in the dictionary.
   - Suggests the closest matching words for misspellings.

---

## Usage

### Prerequisites
Ensure you have a C compiler (e.g., `gcc`) installed on your system.

### Build
To compile the project:
```bash
gcc -o correct_text source/main.c source/library/*.c -I source/library
```

### Run
Use the following command to correct a file:
```bash
./correct_text <dictionary_file_path> <input_file_path>
```

### Example
Given:
- Dictionary file (`dictionary.txt`): 
  ```
  hello
  world
  example
  ```
- Input file (`input.txt`):
  ```
  Helllo wrld exampl
  ```

Command:
```bash
./correct_text dictionary.txt input.txt
```

Output:
```
Processing word 'helllo' (0/3)...
Minimum edit distance for word 'helllo' is 1: hello
Processing word 'wrld' (0/3)...
Minimum edit distance for word 'wrld' is 1: world
Processing word 'exampl' (0/3)...
Minimum edit distance for word 'exampl' is 1: example
```

---

## Unit Tests
To run the tests, compile and execute `tests_main.c`:
```bash
gcc -o tests source/tests_main.c source/library/*.c -I source/library
./tests
```

--

## File Formats

### Dictionary File
- Each line contains one word.
- Example:
    ```
    apple
    banana
    cherry
    ```

### Input File
- Contains arbitrary text.
- Words are separated by non-alphabetic characters.