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
	vec.num_indices_allocated = num_indices;
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
	vec.num_indices_allocated = num_indices;
	vec.vector = pointer;
	return vec;
}


// ================================================================================
// ================================================================================
// eof
