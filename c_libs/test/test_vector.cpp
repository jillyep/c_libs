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

TEST(init_vector, test_one) {
	size_t size = sizeof(int);
	size_t length = 5;
	Vector vec = init_vector(size, length);
	EXPECT_EQ(vec.num_bytes, size);
	EXPECT_EQ(vec.num_indices_allocated, length);
	EXPECT_EQ(vec.active_length, 0);
	free(vec.vector);
}
// ================================================================================
// ================================================================================
// eof
