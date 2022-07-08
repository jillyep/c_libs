// ================================================================================
// ================================================================================
// - File:    vector.c
// - Purpose: Describe the file purpose here
//
// Source Metadata
// - Author:  Jillian Epstein
// - Date:    June 29, 2022
// - Version: 1.0
// - Copyright: Copyright 2022, Jillian Epstein Inc.
// ================================================================================
// ================================================================================
// Include modules here

#include "vector.h"

Vector init_vector(size_t num_bytes, size_t num_indices) {
	// 1. Instantiate the Vector struct.
	// 2. Assign dtype of NONE
	// 3. Determine how much memory to allocate. If there's not enough
	//	  memory, notify the user.
	// 4. Assign memory to vector.
	// 5. Assign active length and allocated length.
	Vector vec;
	void *pointer;
	pointer = malloc(num_indices * num_bytes);
	if (pointer == NULL){
		printf("Unable to allocate memory. Exiting.\n");
		free(vec.vector);
		exit(0);
	}
	vec.dat_type = NONE;
	vec.active_length = 0;
	vec.num_bytes = num_bytes;
	vec.allocated_length = num_indices;
	vec.vector = pointer;
	return vec;
}

// --------------------------------------------------------------------------------

Vector init_type_vector(dtype dat_type, size_t num_indices) {
	Vector vec;
	void *pointer;
	size_t num_bytes;
	if(dat_type == FLOAT) num_bytes = sizeof(float);
	else if (dat_type == DOUBLE) num_bytes = sizeof(double);
	else if (dat_type == CHAR) num_bytes = sizeof(char);
	else if (dat_type == INT) num_bytes = sizeof(int);
	else if (dat_type == SHORTINT) num_bytes = sizeof(short int);
	else if (dat_type == LONG) num_bytes = sizeof(long);
	else if (dat_type == LONGLONG) num_bytes = sizeof(long long);
	else {
		printf("You entered an invalid data type.Instantiating memory allocation to sizeof(int)\n");
		num_bytes = sizeof(int);
	}
	pointer = malloc(num_indices * num_bytes);
	if (pointer == NULL){
		printf("Unable to allocate memory. Exiting.\n");
		free(vec.vector);
		exit(0);
	}
	vec.dat_type = dat_type;
	vec.active_length = 0;
	vec.num_bytes = num_bytes;
	vec.allocated_length = num_indices;
	vec.vector = pointer;
	return vec;
}

// -------------------------------------------------------------------------------- 

// Prototype
// Write function in .c file
// Write test
// Run test
// doc strings
// update readme.rst
// add to git


int push_vector(Vector *vec, void *elements, size_t num_indices){
//1. active length + num_indices, compare to allocated length
//2. if  active > allocated, realloc memory active length * 2
//3. see if vector exceeds memory available (NULL)
//4. assign extra memory to vec.vector
//5. memcopy the new elements into the vector
//6. Update meta data. allocated memory, active length += num_indices,
	size_t dat_size = vec->active_length + num_indices;
	size_t new_size = vec->active_length * 2;
	if (vec->allocated_length < dat_size){
		void *ptr = realloc(vec->vector, new_size * vec->num_bytes);
		if (ptr == NULL){
			printf("Exceeded memory available. Exiting program.\n");
			return 0;
		}
		vec->allocated_length = new_size;
		vec->vector = ptr;
	}
	memcpy((char *)vec->vector + vec->active_length * vec->num_bytes,
			elements, num_indices * vec->num_bytes);
	vec->active_length += num_indices;
	return 1;
}
// ================================================================================
// ================================================================================
// eof
//
//
//
// TODO 1st function: free_vector free vector function; free memory in array and struct
// TODO 2nd function: pop: delete indice of choice
