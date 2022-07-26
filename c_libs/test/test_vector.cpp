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
	Vector vec = init_vector(length, size);
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
	push_vector(&vec, a, length);
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

// -------------------------------------------------------------------------------- 

TEST(test_free_vector, free_vec){
	int a[] = {1, 2, 3};
	int length = 3;
	Vector vec = init_type_vector(INT, length);
	push_vector(&vec, a, length);
	free_vector(&vec);
	EXPECT_EQ(vec.allocated_length, 0);
	EXPECT_EQ(vec.active_length, 0);
	EXPECT_EQ(vec.num_bytes, 0);
	EXPECT_TRUE(vec.vector == NULL);
}

// -------------------------------------------------------------------------------- 

TEST(pop_vector, pop_vec){
	int a[] = {1, 2, 3};
	int length = 3;
	Vector vec = init_type_vector(INT, length);
	push_vector(&vec, a, length);
	pop_vector(&vec, 2);
	for (size_t i = 0; i < vec.active_length; i++){
		EXPECT_EQ(a[i], ((int *) vec.vector)[i]);
	}
}

// -------------------------------------------------------------------------------- 

TEST (insert_vector, insert_vec) {
	int a[] = {1, 2, 3};
	int b[] = {4, 5, 6};
	size_t length = 3;
	size_t insert_indice = 2;
	Vector vec = init_type_vector(INT, length);
	push_vector(&vec, a, length);
	insert_vector(&vec, b, length, insert_indice);
	//for (int i = 0; i < vec.active_length; i++) {
	//	printf("%d\n", ((int *)vec.vector)[i]);
//	}
}

// -------------------------------------------------------------------------------- 

TEST (delete_vector_value, del_vec) {
	int a[] = {1, 2, 3, 3, 4, 5, 6, 7, 2};
	int del_value = 3;
	size_t length = 9;
	Vector vec = init_type_vector(INT, length);
	push_vector(&vec, a, length);
	delete_vector_value(&vec, &del_value);
//	for (int i = 0; i < vec.active_length; i++) {
	//	printf("%d\n", ((int *)vec.vector)[i]);
//	}
}

// -------------------------------------------------------------------------------- 


TEST (replace_index_vector, replace_vec) {
	int a[] = {1, 2, 3, 4};
	int rep_value = 8;
	size_t rep_length = 1;
	size_t length = 4;
	size_t index = 2;
	Vector vec = init_type_vector(INT, length);
	push_vector(&vec, a, length);
	replace_index_vector(&vec, index, &rep_value, rep_length);
	for (int i = 0; i < vec.active_length; i++) {
		printf("%d\n", ((int *)vec.vector)[i]);
	}
}
	// eof
