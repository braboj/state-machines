# Hilscher DTC Technical Task

## Task Description
Implement the following state diagram in C. The state machine represents a 
interface that can either 

![task state machine](assets/images/task_state_machine.png)


## Environment

The project used the following tools and libraries:

- GCC compiler
- Windows 7 or later
- CodeBlocks IDE
- Doxygen

## How to run the code

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
