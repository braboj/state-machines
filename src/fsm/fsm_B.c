/* General information
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + Description : Finite state machine (table-driven switching)
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
 * @file fsm_B.c
 * @brief FSM : Table-driven switching implementation
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


//-----------------------------------------------------------------------------
/** @brief Common text descriptors for the states used throughout the program
 */

const char *FSM_B_STATE_TEXT[] = {"ENTRY","PRINT_F","PRINT_R","CLEANUP"};


//-----------------------------------------------------------------------------
/** @brief Output function type definition
 */

typedef void FSM_FUNC_OUT(vector *v, char *input, FSM_STATES state);


//-----------------------------------------------------------------------------
/** @brief Switching table definition
 */

typedef struct FSM_TABLE_{
    FSM_STATES state;
    FSM_EVENTS event;
    FSM_STATES next;
    FSM_FUNC_OUT* output;
}FSM_TABLE;


void Entering_Action(vector *v, char *input, FSM_STATES old_state);
void Printing_Action(vector *v, char *input, FSM_STATES old_state);
void PrintingRev_Action(vector *v, char *input, FSM_STATES old_state);
void Cleanup_Action(vector *v, char *input, FSM_STATES old_state);


//-----------------------------------------------------------------------------
/** @brief FSM table configuration
    @brief Format : {STATE, EVENT, NEXT STATE, ACTION}
 */

FSM_TABLE FSM[] = {
    {Entering, EnterKey, Printing, Printing_Action},
    {Entering, SpaceKey, Cleanup, Cleanup_Action},
    {Entering, OtherEvent, Entering, Entering_Action},
    {Printing, EnterKey, PrintingRev, PrintingRev_Action},
    {Printing, BackSpaceKey, Entering, Entering_Action},
    {Printing, SpaceKey, Cleanup, Cleanup_Action},
    {Printing, OtherEvent, Printing, Printing_Action},
    {PrintingRev, BackSpaceKey, Printing, Printing_Action},
    {PrintingRev, SpaceKey, Cleanup, Cleanup_Action},
    {PrintingRev, OtherEvent, PrintingRev, PrintingRev_Action},
    {Cleanup, EnterKey, Entering, Entering_Action},
    {Cleanup, OtherEvent, Cleanup, Cleanup_Action},
};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ 3. Implementation
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM_B_Loop
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief FSM : Table driven switching implementation
**/

void FSM_B_Loop()
{
    char input;
    FSM_STATES state;
    vector data;
    int s;

    //FSM initialization
    input = '\0';
    state = Entering;
    vector_init(&data);
    printf("\n%-8s %s",FSM_B_STATE_TEXT[Entering],FSM_PROMPT);

    //FSM switching
    while (1)
    {
        input = getch();

        s = sizeof(FSM)/sizeof(FSM_TABLE);

        //Loop through table entries
        for(int i=0;i<s;i++)
        {
            //Current state found in the table
            if (FSM[i].state==state)
            {
                //Event found in the table
                if (FSM[i].event==input)
                {
                    FSM[i].output(&data, &input, state);
                    state = FSM[i].next;
                    break;
                }

                //Event not found in the table
                if (FSM[i].event==OtherEvent)
                {
                    FSM[i].output(&data, &input, state);
                    break;
                }

            }
        }
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
        printf("\n%-8s %s",FSM_B_STATE_TEXT[Entering],FSM_PROMPT);
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

    printf ("\n%-8s %s",FSM_B_STATE_TEXT[Printing],FSM_PROMPT);

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

    printf ("\n%-8s %s",FSM_B_STATE_TEXT[PrintingRev],FSM_PROMPT);

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

void Cleanup_Action(vector *v, char *input, FSM_STATES state)
{
    printf ("\n%-8s %s",FSM_B_STATE_TEXT[Cleanup],FSM_PROMPT);
    vector_reset(v);
}

