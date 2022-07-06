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
// ================================================================================
// ================================================================================
// eof
