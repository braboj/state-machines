/* General information
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + Description : Finite state machine (code-based switching)
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
 * @file fsm_A.c
 * @brief Fixed code implementation of the finite state machine
 * @author Branimir Georgiev
 * @date 03.11.2018
 * @see http://www.hilscher.com
 */

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ 1. Preprocessor
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#include "fsm.h"
#include "vector.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ 2. Declarations
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @brief Common text descriptors for the states used in the program
 */

const char *FSM_A_STATE_TEXT[] = {"ENTRY","PRINT_F","PRINT_R","CLEANUP"};

static void FSM_In(char *input);
static void FSM_Next(char input, FSM_STATES *state);
static void FSM_Out(char *input, FSM_STATES state, vector *v);

static FSM_STATES Entering_Transition (FSM_EVENTS event);
static FSM_STATES Printing_Transition (FSM_EVENTS event);
static FSM_STATES PrintingRev_Transition (FSM_EVENTS event);
static FSM_STATES Cleanup_Transition (FSM_EVENTS event);

static void Entering_Action(vector *v, char *input, FSM_STATES old_state);
static void Printing_Action(vector *v, char *input, FSM_STATES old_state);
static void PrintingRev_Action(vector *v, char *input, FSM_STATES old_state);
static void Cleanup_Action(vector *v, char *input, FSM_STATES old_state);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ 3. Implementation
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM_A_Loop
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief FSM : Code based switching implementation

This function checks the user input. This function might be configured to
accommodate the needs of the project. This might include register, ports and
other sources.

**/

void FSM_A_Loop()
{
    char user_input;
    FSM_STATES state;
    vector data;

    //Initialization
    user_input='\0';
    state = Entering;
    vector_init(&data);
    printf("\n%-8s %s",FSM_A_STATE_TEXT[Entering],FSM_PROMPT);

    //Main loop
    while(1)
    {
        //Wait for user input
        FSM_In(&user_input);

        //Evaluate user input and generate next state
        FSM_Next(user_input, &state);

        //Validate data and generate output
        FSM_Out(&user_input, state, &data);

    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM_In
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Evaluates the user input
  * @param input : User input

This function checks the user input. This function might be configured to
accommodate the needs of the project. This might include register, ports and
other sources.

**/

static void FSM_In(char *input)
{
    *input = getch();
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM_Next
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Calculates the next state based on user input and current state
  * @param input : User input
  * @param state : Current state

This function dispatches events by the user and calls the relevant functions
to determine the next state. This function should be updated to accommodate
any changes performed on the state machine specification.

**/

static void FSM_Next(char input, FSM_STATES *state)
{

    switch(*state)
    {
        case Entering:
            *state=Entering_Transition(input);
            break;

        case Printing:
            *state=Printing_Transition(input);
            break;

        case PrintingRev:
            *state=PrintingRev_Transition(input);
            break;

        case Cleanup:
            *state=Cleanup_Transition(input);
            break;

        default:
            break;
    }

}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM_Out
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Performs actions associated with the state and formates the output
  * @param input : User input
  * @param state : Current state
  * @param v     : User data

This function generates the output of the state machine. It calls all the
functions associated with the states and should be updated to accommodate
any changes performed on the state machine specification.

**/

static void FSM_Out(char *input, FSM_STATES state, vector *v)
{
    static FSM_STATES state_old = Entering;

    //Standard output formatting
    switch(state)
    {
        case Entering:
            Entering_Action(v,input, state_old);
            break;

        case Printing:
            Printing_Action(v,input, state_old);
            break;

        case PrintingRev:
            PrintingRev_Action(v,input, state_old);
            break;

        case Cleanup:
            Cleanup_Action(v, input, state_old);
            break;

        default:
            break;
        }

    state_old=state;

}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Entering_Transition
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Entering state transition function
  * @param event : User event

Entering transition logic required by the specification. Should be updated
if the specification of the state machine changes.

**/

static FSM_STATES Entering_Transition (FSM_EVENTS event)
{
    switch (event)
    {
        case EnterKey:
            return Printing;
            break;

        case SpaceKey:
            return Cleanup;
            break;

        default:
            return Entering;
            break;
    }
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Printing_Transition
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Printing state transition function
  * @param event : User event

Printing transition logic required by the specification. Should be updated
if the specification of the state machine changes.

**/

static FSM_STATES Printing_Transition (FSM_EVENTS event)
{
    switch (event)
    {
        case BackSpaceKey:
            return Entering;
            break;

        case EnterKey:
            return PrintingRev;
            break;

        case SpaceKey:
            return Cleanup;
            break;

        default:
            return Printing;
            break;
    }
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PrintingRev_Transition
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief PrintingReverse state transition function
  * @param event : User event

PrintingRev transition logic required by the specification. Should be updated
if the specification of the state machine changes.

**/

static FSM_STATES PrintingRev_Transition (FSM_EVENTS event)
{
    switch (event)
    {
        case BackSpaceKey:
            return Printing;
            break;

        case SpaceKey:
            return Cleanup;
            break;

        default:
            return PrintingRev;
            break;

    }
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Cleanup_Transition
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Cleanup state transition function
  * @param event : User event

Cleanup transition logic required by the specification. Should be updated
if the specification of the state machine changes.

**/

static FSM_STATES Cleanup_Transition (FSM_EVENTS event)
{
    switch (event)
    {
        case EnterKey:
            return Entering;
            break;

        default:
            return Cleanup;
            break;
    }
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Entering_Action
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Entering actions
  * @param v     : User data
  * @param input : User input
  * @param state : State

Entering output actions required by the specification. Should be updated
if the specification of the state machine changes.

**/

void Entering_Action(vector *v, char *input, FSM_STATES state)
{
    static FSM_STATES old_state;

    //Transition to entering triggers a vector dump
    if (old_state != state)
    {
        printf("\n%-8s %s",FSM_A_STATE_TEXT[Entering],FSM_PROMPT);
        vector_dump(v);
    }

    //Check if input is not alphanumeric
    if (!isalnum(*input))
    {
        return;
    }
    else
    {
        if (vector_count(v) < FSM_MAX_ENTRY) {
            putchar(*input);
            vector_add(v, (int) *input);
        }

    }

    old_state = state;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Printing_Action
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Printing actions
  * @param v     : User data
  * @param input : User input
  * @param state : State

Printing output actions required by the specification. Should be updated
if the specification of the state machine changes.

**/

void Printing_Action(vector *v, char *input, FSM_STATES state)
{
    static FSM_STATES old_state;
    int c;

    c=vector_count(v);

    printf ("\n%-8s %s",FSM_A_STATE_TEXT[Printing],FSM_PROMPT);

    for(int i=0;i<c;i++)
    {
        putchar(v->data[i]);
    }

    old_state = state;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PrintingRev_Action
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief PrintingReverse actions
  * @param v     : User data
  * @param input : User input
  * @param state : State

PrintingRev output actions required by the specification. Should be updated
if the specification of the state machine changes.

**/

void PrintingRev_Action(vector *v, char *input, FSM_STATES state)
{
    int c;

    c=vector_count(v);

    printf ("\n%-8s %s",FSM_A_STATE_TEXT[PrintingRev],FSM_PROMPT);

    for(int i=(c-1);i>=0;i--)
    {
        putchar( (int) v->data[i]);
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Cleanup_Action
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Cleanup actions
  * @param v     : User data
  * @param input : User input
  * @param state : State

Cleanup output actions required by the specification. Should be updated
if the specification of the state machine changes.

**/

static void Cleanup_Action(vector *v, char *input, FSM_STATES state)
{
    printf ("\n%-8s %s",FSM_A_STATE_TEXT[Cleanup],FSM_PROMPT);
    vector_reset(v);
}
