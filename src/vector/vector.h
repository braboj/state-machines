/* General information
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + Description : Vector data type interface
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
 * @file vector.h
 * @brief Interface of the vector data type
 * @author Branimir Georgiev
 * @date 03.11.2018
 * @see http://www.hilscher.com
 */

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 1. Preprocessor
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 2. Declarations
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Vector structure
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Vector structure used to build the dynamic array
 */

typedef struct vector_ {
    void** data;    /**< Pointer to the array storing the variable data */
    int index;      /**< Index of last available element */
} vector;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_init
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Initialize vector
  * @param v : address to the vector structure
  * @return 0=>Operation successful, 1=>Operation failed
**/

int vector_init(vector *v);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_free
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Free the memory reserved by the vector
  * @param v : address to the vector structure
**/

void vector_free(vector *v);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_add
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Adds an additional element to the vector
  * @param v : address to the vector structure
  * @param e : element of any type to add
  * @return 0=>Operation successful, 1=>Operation failed
**/

int vector_add(vector *v, void *e);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_remove
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Removes an element from the vector
  * @param v : address to the vector structure
  * @param i : index of the element to be removed
**/

void vector_remove(vector *v, int i);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_count
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Return the total number of elements
  * @param v  : address to the vector structure
**/

int vector_count(vector *v);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_dump
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Dump all elements of the vector
  * @param v  : address to the vector structure
**/

void vector_dump(vector *v);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_set
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Set the value of an element with a given index
  * @param v  : address to the vector structure
  * @param e  : value of the element
  * @param i  : index of the element in the vector

**/

void vector_set(vector *v, void *e, int index);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_get
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Get the value of an element with a given index
  * @param v  : address to the vector structure
  * @param i  : index of the element in the vector
**/

void *vector_get(vector *v, int index);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// vector_reset
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/** @brief Resets the vector
  * @param v  : address to a vector structure
**/

int vector_reset(vector *v);


#endif //VECTOR_H_INCLUDED
