/* General information
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + Description : Vector data type implementation
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
 * @file vector.c
 * @brief Implementation of the vector data type
 * @author Branimir Georgiev
 * @date 03.11.2018
 * @see http://www.hilscher.com
 */


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 1. Preprocessor
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 2. Declarations
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 3. Implementation
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_init
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// This function requires the address of a vector structure. It reserves some
/// memory by using malloc. The index of the first free element will be 0. If
/// the function cannot reserve memory it shall return non-zero values.
/// @todo Check if memset is suitable to initialize memory



int vector_init(vector *v)
{
    v->index = 0 ;
    v->data = malloc(sizeof(void *));

    //Check if operation was successful
    if (v->data == NULL) {
        return 1;
    }

    return 0;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_free
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// This function releases the memory used by the vector structure. It uses the
/// standard free function.

void vector_free(vector *v)
{
    free(v->data);
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_add
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// This function adds the value of the element to the dynamic array and then
/// increments the index to point to the next free element. The vector then is
/// resized by using realloc and the the incremented index.
/// @todo Evaluate performance of realloc

int vector_add(vector *v, void *e)
{
    v->data[v->index] = e;
    v->index++;
    v->data = realloc(v->data, (sizeof(void*)) * (v->index + 1));

    //Check if operation was successful
    if (v->data == NULL) {
        return 1;
    }

    return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_remove
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// This function removes the value of the element to the dynamic array and then
/// rearranges the index values.

void vector_remove(vector *v, int i)
{
    if (i >= v->index) {
        return;
    }

    for (int a = i, b = i; a < v->index; a++) {
        v->data[b] = v->data[a];
        b++;
    }

    v->index--;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_count
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// This function returns the total number of elements in the vector

int vector_count(vector *v)
{
    return ((v->index));
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_dump
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// This function goes through the dynamic array and prints all possible values
/// as characters.
/// @todo Test the function with strings as elements of the vector

void vector_dump(vector *v)
{
    for (int i=0 ; i < v->index ; i++)
    {
        printf("%c",(int) v->data[i]);
    }
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_set
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// This function sets the value of an element with a given index. It also
/// checks if the index given in the function call is not exceeding the index
/// of the last free element.

void vector_set(vector *v, void *e, int i)
{
    if (i >= v->index) {
        return;
    }

    v->data[i] = e;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_get
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// This function gets the value of an element with a given index. It also
/// checks if the index given in the function call is not exceeding the index
/// of the last free element.

void *vector_get(vector *v, int i)
{
    if (i >= v->index) {
        return NULL;
    }

    return v->data[i];
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_reset
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// This function updates the value of an element with a given index. It also
/// checks if the index given in the function call is not exceeding the index
/// of the last free element.

int vector_reset(vector *v)
{
   vector_free(v);
   return vector_init(v);
}
