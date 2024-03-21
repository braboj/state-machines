# Hilscher DTC Technical Task

## Task Description
Implement the followin state diagram in C.

![task state machine](assets/task_state_machine.png)


## Pre-requisites

- GCC compiler
- Windows 7 or later

## How to run the code

### Select one of the following options:

1. Uncomment FSM_A or FSM_B in the ./src/main.c file to run the respective state machine.
2. Uncomment the TEST macro in the ./src/main.c file to run the test cases.
3. Run the following commands in the terminal:

```bash
$ cd <path_to_project_directory>
$ gcc -o main ./src/main.c
$ ./main
```

## How to build the documentation
```bash
$ doxygen Hilscher_Doxyfile
```
