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

Vector init_vector(size_t allocated_length, size_t num_bytes_per_indice) {
	Vector vec;
	void *pointer;
	pointer = malloc(allocated_length * num_bytes_per_indice);
	if (pointer == NULL){
		printf("Unable to allocate memory. Exiting.\n");
		free(pointer);
		exit(0);
	}
	vec.dat_type = NONE;
	vec.num_bytes = num_bytes_per_indice;
	vec.active_length = 0;
	vec.allocated_length = allocated_length;
	vec.vector = pointer;
	return vec;
}

// --------------------------------------------------------------------------------

Vector init_type_vector(dtype dat_type, size_t allocated_length) {
	Vector vec;
	if(dat_type == FLOAT) {
		vec.num_bytes = sizeof(float);
		vec.dat_type = dat_type;
	}
	else if (dat_type == DOUBLE) {
		vec.num_bytes = sizeof(double);
		vec.dat_type = dat_type;
	}
	else if (dat_type == CHAR) {
		vec.num_bytes = sizeof(char);
		vec.dat_type = dat_type;
	}
	else if (dat_type == INT) {
		vec.num_bytes = sizeof(int);
		vec.dat_type = dat_type;
	}
	else if (dat_type == SHORTINT) {
		vec.num_bytes = sizeof(short int);
		vec.dat_type = dat_type;
	}
	else if (dat_type == LONG) {
		vec.num_bytes = sizeof(long);
		vec.dat_type = dat_type;
	}
	else if (dat_type == LONGLONG) {
		vec.num_bytes = sizeof(long long);
		vec.dat_type = dat_type;
	}
	else {
		printf("You entered an invalid data type. Instantiating memory allocation to sizeof(int)\n");
		vec.num_bytes = sizeof(int);
		vec.dat_type = INT;
	}
	void *pointer = malloc(allocated_length * vec.num_bytes);
	if (pointer == NULL){
		printf("Unable to allocate memory. Exiting.\n");
		free(pointer);
		vec.num_bytes = 0;
		vec.dat_type = 0;
		exit(0);
	}
	vec.active_length = 0;
	vec.allocated_length = allocated_length;
	vec.vector = pointer;
	return vec;
}

// -------------------------------------------------------------------------------- 


int push_vector(Vector *vec, void *elements, size_t push_length) {
	if (vec->allocated_length < vec->active_length + push_length) {
		size_t new_size = (vec->allocated_length + push_length) * vec->num_bytes * 2;
		void *ptr = realloc(vec->vector, new_size);
		if (ptr == NULL){
			printf("Exceeded memory available. Exiting program.\n");
			free(ptr);
			return 0;
		}
		vec->allocated_length = new_size;
		vec->vector = ptr;
	}
	memcpy(((char *)vec->vector) + vec->active_length * vec->num_bytes,
			elements, push_length * vec->num_bytes);
	vec->active_length += push_length;
	return 1;
}

// -------------------------------------------------------------------------------- 

void free_vector(Vector *vec){
	free(vec->vector);
	vec->active_length = 0;
	vec->allocated_length = 0;
	vec->num_bytes = 0;
	vec->dat_type = 0;
	vec->vector = NULL;
}


// --------------------------------------------------------------------------------

void pop_vector(Vector *vec, int pop_indice){
	memmove(((char *)vec->vector) + (vec->num_bytes * pop_indice),
			((char *) vec->vector) + (pop_indice + 1) * vec->num_bytes,
			(vec->active_length - pop_indice) * vec->num_bytes);
	vec->active_length -= 1;
}

// --------------------------------------------------------------------------------

int insert_vector(Vector *vec, void *elements, size_t insert_length, size_t insert_indice) {
	if (vec->allocated_length < vec->active_length + insert_length) {
		size_t new_size = (vec->active_length + insert_length) * vec->num_bytes * 2;
		void *ptr = realloc(vec->vector, new_size);
		if (ptr == NULL) {
			printf("Not enough memory available.\n");
			free(ptr);
			return 0;
		}
		vec->vector = ptr;
		vec->allocated_length = new_size;
	}
	memmove(((char *) vec->vector) + (insert_indice + insert_length) * vec->num_bytes,
			((char *) vec->vector) + (insert_indice * vec->num_bytes),
			(vec->active_length - insert_indice) * vec->num_bytes);
	memcpy(((char *) vec->vector) + (insert_indice * vec->num_bytes), elements,
				insert_length * vec->num_bytes);
	vec->active_length += insert_length;
	return 1;
}

// --------------------------------------------------------------------------------


void delete_vector_value(Vector *vec, void *delete_value) {
	for (int i = 0; i < vec->active_length; i++){
		int result = memcmp(((char *)vec->vector) + (i * vec->num_bytes),
				((char *)delete_value), vec->num_bytes);
		if (result == 0) {
			pop_vector(vec, i);
			i -= 1;
		}
	}
}

// -------------------------------------------------------------------------------- 

void replace_index_vector(Vector *vec, size_t index, void *replace_value, size_t replace_length) {
	pop_vector(vec, index);
	insert_vector(vec, replace_value, replace_length, index);
}

// --------------------------------------------------------------------------------

void replace_vector_value(Vector *vec, void *delete_value, void *replace_value, size_t replace_length) {
	for (int i = 0; i < vec->active_length; i++) {
		int result = memcmp(((char *)vec->vector) + (i * vec->num_bytes),
				((char *)delete_value), vec->num_bytes);
		if (result == 0) {
			replace_index_vector(vec, i, replace_value, replace_length);
		}
	}
}

// --------------------------------------------------------------------------------

void delete_vector_duplicates(Vector *vec) {
	for (int i = 0; i < vec->active_length - 1; i++) {
		for (int j = i + 1; j < vec->active_length; j++) {
			int result = memcmp(((char *)vec->vector) + (i * vec->num_bytes),
					((char *)vec->vector) + (j * vec->num_bytes),
					vec->num_bytes);
			if (result == 0) {
				pop_vector(vec, j);
			}
		}
	}
}

// ================================================================================
// ================================================================================
// eof
