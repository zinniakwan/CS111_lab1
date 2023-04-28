## UID: 205777626
(IMPORTANT: Only replace the above numbers with your true UID, do not modify spacing and newlines, otherwise your tarfile might not be created correctly)

## Pipe Up

This program is a low level implementation of the pipe operator in shells. Users will pass in executables as command line arguments to the program, and output will be similar to if pipe operator exists between each executable.

## Building

run the following command:
    make

## Running

For example, if we are trying to simulate the terminal command (ls | cat |wc), we would run:
    ./pipe ls cat wc
    (all arguments are sepearted by a space, we cannot handle executables that require flags or input)

The output of this command should be the same as the one we attempted to simulate. Both output:
        7   7   63

## Cleaning up

run the following command:
    make clean
