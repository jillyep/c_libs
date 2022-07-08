// ================================================================================
// ================================================================================
// - File:    vector.h
// - Purpose: This file contains the prototype, structures, and enums used
//            in vector.c.
//
// Source Metadata
// - Author:  Jillian Epstein
// - Date:    June 29, 2022
// - Version: 1.0
// - Copyright: Copyright 2022, Jillian Epstein Inc.
// ================================================================================
// ================================================================================
// Include modules here

#ifndef vector_H
#define vector_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief A Container for the data type of the elements of the struct Vector
 *
 * @param FLOAT represents a 4 byte float.
 * @param DOUBLE represents an 8 byte double.
 * @param CHAR represents a 1 byte char.
 * @param INT represents a 4 byte int.
 * @param STRING represents a character string.
 * @param SHORTINT represents a 2 byte short integer.
 * @param LONG presents an 8 byte integer.
 * @param LONGLONG is a 16 byte integer.
 * @param NONE is user-defined data type.
 */

typedef enum
{
	FLOAT,
	DOUBLE,
	CHAR,
	INT,
	STRING,
	SHORTINT,
	LONG,
	LONGLONG,
	NONE
}	dtype;
//--------------------------------------------------------------------------------

/**
 * @brief A Container for the dynamically allocated array and related metadata
 *
 * @struct Vector
 * A container for a dynamic array and metadata

 * @param Vector::vector
 *    A pointer to an array in heap memory
 * @param Vector::active_length
 *    The number of indices with assigned data
 * @param Vector::allocated_length
 *    The total number of allocated indices in memory
 * @param Vector::num_bytes
 *    The number of bytes consumed by a single indices
 * @param Vector::dat_type
 *    The data type.  Must use data types allodated in dtype enum
 */
typedef struct
{
	void *vector;
	size_t active_length;
	size_t allocated_length;
	size_t num_bytes;
	dtype dat_type;
} Vector;
//--------------------------------------------------------------------------------

/**
 * Instantiates a Vector container where the user can determine the number of
 * bytes allocated to each vector indice. This function allocates the vector
 * in heap memory.
 *
 * @param num_bytes The number of bytes consumed by each index in the array
 * @param num_indices The users guess for the total number of required indices
 * in the vector.
 * @return vec A Vector container
 *
 * @code
 * // - Create a dynamically allocated array container for integers, with allocated
 * // memory for 5 indices.
 * Vector vec = init_vector(sizeof(int), 5);
 * @endcode
 */

Vector init_vector(size_t num_bytes, size_t num_indices);

//--------------------------------------------------------------------------------

/**
 * Instantiates a Vector container where the user can pass to the function
 * an enum value representing the data type.
 *
 * @param dat_type An enum data type
 * @param num_indices The user guess for the initial number of allocated
 *                    indices
 * @return vec A Vector container
 *
 * @code
 * // Create a dynamically allocated array container for integers, with allocated
 * // memory for 5 indices
 * Vector vec = init_type_vector(INT, 5)
 * @endcode
 */
Vector init_type_vector(dtype dat_type, size_t num_indices);

//--------------------------------------------------------------------------------

int push_vector(Vector *vec, void *elements, size_t num_indices);

#endif /* vector_H */
// ================================================================================
// ================================================================================
// eof
