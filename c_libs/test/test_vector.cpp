// ================================================================================
// ================================================================================
// - File>    test.cpp
// - Purpose: This file implements google test as a method to test c code.
//            Describe the type of testing to be completed
//
// Source Metadata
// - Author:  Jillian Epstein
// - Date:    June 29, 2022
// - Version: 1.0
// - Copyright: Copyright 2022, Jillian Epstein Inc.
// ================================================================================
// ================================================================================
// - Begin test

#include <gtest/gtest.h>

extern "C" {
#include "vector.h"
}
// -------------------------------------------------------------------------------- 
/* This function will test the init_vector to see if it correctly
 * allocates memory for a user defined dynamic array.
*/

TEST(init_vector, test_one) {
	size_t size = sizeof(int);
	size_t length = 5;
	Vector vec = init_vector(size, length);
	EXPECT_EQ(vec.num_bytes, size);
	EXPECT_EQ(vec.allocated_length, length);
	EXPECT_EQ(vec.active_length, 0);
	free(vec.vector);
}

// -------------------------------------------------------------------------------- 

/* This function will test the init_type_vector to see if it correctly
 * allocates memory for a user defined dynamic array.
*/

TEST(test_initialize_vector, type_vec) {
	size_t length = 5;
	Vector vec = init_type_vector(INT, length);
	EXPECT_EQ(vec.num_bytes, sizeof(int));
	EXPECT_EQ(vec.allocated_length, length);
	EXPECT_EQ(vec.active_length, 0);
	free(vec.vector);
}

// -------------------------------------------------------------------------------- 

/* This function will test the push_vector to see if it correctly
 * pushes array data to the vector.
*/

TEST(test_push_vector, push_array) {
	int a[] = {1, 2, 3};
	int length = 3;
	Vector vec = init_type_vector(INT, length);
	for (size_t i = 0; i < vec.active_length; i++){
		EXPECT_EQ(a[i], ((int *) vec.vector)[i]);
	}
}

// -------------------------------------------------------------------------------- 
//
/* This function will test the push vector to see if it correctly
 * pushes scalar data to the vector.
 */

TEST(test_push_vector, push_scalar){
	int a = 3;
	int length = 1;
	Vector vec = init_type_vector(INT, length);
	push_vector(&vec, &a, 1);
	EXPECT_EQ(((int *) vec.vector)[0], a);
}

// ================================================================================
// ================================================================================
// eof
