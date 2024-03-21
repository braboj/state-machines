/* General information
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + Description : Hilscher test (finite state machine implementation)
 + Author      : Branimir Georgiev
 + Company     :
 + Tel.Nr.     : ++359885759241
 + E-mail      : braboj@abv.bg
 + Created     : 03.11.2018
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + Notes       :
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

/**
 * @file main.c
 * @brief Main program for the state machine
 * @author Branimir Georgiev
 * @date 04.11.2018
 * @see http://www.hilscher.com
 */


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ 1. Preprocessor
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fsm.h"
#include "vector.h"

#define TEST
//#define FSM_A
#define FSM_B


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ 2. Declarations
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ 3. Implementation
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_test
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** \brief Simple vector unit testing
 */

 void vector_test()
 {
    vector v;
    int d=0;

    v.data = NULL;

    vector_init(&v);
    assert(v.data != NULL);

    vector_add(&v,1);
    assert(v.data[0] == 1);

    vector_set(&v,2,0);
    assert(v.data[0] == 2);

    d=vector_get(&v,0);
    assert(d == 2);

    vector_remove(&v,0);
    assert(v.index==0);

    vector_add(&v,3);
    assert(v.data[0] == 3);

    vector_free(&v);
    assert(v.data[0] != 3);

    vector_init(&v);
    vector_add(&v,1);
    vector_add(&v,2);
    vector_add(&v,3);
    d=vector_count(&v);
    assert(d == 3);
 }


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// print_info
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** \brief Prints user instructions and FSM version before state machine loop
 */

void print_info()
{

    #ifdef FSM_A
        printf("Hilscher FSM (A) : Code-based switching logic\n\n");
    #endif

    #ifdef FSM_B
        printf("Hilscher FSM (B) : Table-driven switching logic\n\n");
    #endif

    printf("-------------------------------------------------------------------------------------------\n");
    printf("ENTRY   : User types text. Enter(->print) or Space(->cleanup).\n");
    printf("PRINT_F : Print typed text. Enter(->print reverse) or BackSpace(->user entry)\n");
    printf("PRINT_R : Print typed text in reverse. Backspace(->print normal) or Space(->cleanup)\n");
    printf("CLEANUP : Resets the internal buffer. Enter(->user entry)\n");
    printf("-------------------------------------------------------------------------------------------\n\n");
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Main
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** \brief Main program which runs the loop of the state machine
 */

int main()
{

    print_info();

    #ifdef TEST
        vector_test();
    #endif

    #ifdef FSM_A
        FSM_A_Loop();
    #endif

    #ifdef FSM_B
        FSM_B_Loop();
    #endif
}

