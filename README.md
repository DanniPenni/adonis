# ADONIS

ADONIS is a C program that renders a window-based GUI in ASCII. 

## Requirements 

CMake version 4.0 and above.
Ninja.

## Installation & Executable 

Once you have the repository cloned:
```console
$ mkdir build && cd build
$ cmake -G Ninja ..
$ ninja
$ ./adonis
```

## Usage

Current functionality 
- You can interact with the program using the input-bar.
- Once you press enter, the command is saved in the program and displayed on the screen.

WIP :)
- Each window runs a process and displays its output. This is the main functionality of the program; Seeing the outputs of multiple (concurrently running) processes simultaenously.
- Interaction with the program to:
  * Create new windows (and link them to the executable to-be-displayed in them).
  * Send inputs into existing windows.

## Contributing

TBD.
