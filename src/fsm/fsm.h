/* General information
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + Description : Finite state machine interface
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
 * @file fsm.h
 * @brief Finite state machine interface
 * @author Branimir Georgiev
 * @date 03.11.2018
 * @see http://www.hilscher.com
 */

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 1. Preprocessor
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef FSM_DEFINITIONS_H_INCLUDED
#define FSM_DEFINITIONS_H_INCLUDED

#define FSM_PROMPT ":"      //Prompt after state text
#define FSM_MAX_ENTRY 1024  //Maximum number of symbols entered by the user


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 2. Declarations
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM states enumeration
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Defines all the possible states of the finite state machine
 */

typedef enum fsm_states_
{
    Entering,       /**< User enters symbols */
    Printing,       /**< Symbols are printed as entered */
    PrintingRev,    /**< Symbols are printed in reverse */
    Cleanup,        /**< All symbols are cleared */
}FSM_STATES;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM events enumeration
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Defines all the possible events evaluated by the finite state machine
 */

typedef enum fsm_events_
{
    OtherEvent=-1,  /**< Other events */
    BackSpaceKey=8, /**< ASCII = 08 */
    LineFeed=10,    /**< ASCII = 10 */
    EnterKey=13,    /**< ASCII = 13 */
    SpaceKey=32     /**< ASCII = 32 */
}FSM_EVENTS;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM_A_Loop
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Finite state machine with fixed code approach
**/

void FSM_A_Loop();


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FSM_B_Loop
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Finite state machine with table-driven approach
**/

void FSM_B_Loop();


#endif // FSM_DEFINITIONS_H_INCLUDED
