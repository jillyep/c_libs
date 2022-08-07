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
				j -= 1;
			}
		}
	}
}

// --------------------------------------------------------------------------------


void unique_vector_values(Vector *vec) {
	char *temp1;
	char *temp2;
	size_t flag;
	for (int i = 0; i < vec->active_length - 1; i++) {
		flag = 0;
		temp1 = ((char *)vec->vector) + i * vec->num_bytes;
		for (int j = i + 1; j < vec->active_length; j++) {
			temp2 = ((char *)vec->vector) + j * vec->num_bytes;
			int result = memcmp(temp1, temp2, vec->num_bytes);
			if (result == 0) {
				flag = 1;
				pop_vector(vec, j);
				j -= 1;
			}
		}
		if (flag == 1) {
			pop_vector(vec, i);
			flag = 0;
			i -= 1;
		}

	}
}

// --------------------------------------------------------------------------------

int sort_vector(Vector *vec, order order_type) {
	int temp;
	int min_idx;
	int var_one, var_two;
	for (size_t i = 0; i < vec->active_length - 1; i++){
		min_idx = i;
		temp = ((int *)vec->vector)[min_idx];
		for (size_t j = i + 1; j < vec->active_length; j++) {
			var_one = ((int *)vec->vector)[min_idx];
			var_two = ((int *)vec->vector)[j];
			if (var_two < var_one && order_type == ASCENDING){
				min_idx = j;
				temp = ((int *)vec->vector)[min_idx];
			}
			else if (var_two > var_one && order_type == DESCENDING) {
				min_idx = j;
				temp = ((int *)vec->vector)[min_idx];
			}
		}
		* (int *) ((char *) vec->vector + min_idx * vec->num_bytes) = ((int *) vec->vector)[i];
		* (int *) ((char *) vec->vector + i * vec->num_bytes) = temp;
	}
	return 1;
}
/*	int compare;
	char *var_one[vec->num_bytes];
	char *var_two[vec->num_bytes];
	for (size_t i = 0; i < vec->active_length - 1; i++) {
		for (size_t j = 0; j < vec->active_length; j++) {
			memcpy(var_one, ((char *)vec->vector) + (i * vec->num_bytes),vec->num_bytes);
			memcpy(var_two, ((char *)vec->vector) + (j * vec->num_bytes), vec->num_bytes);
			compare = memcmp(var_one, var_two, vec->num_bytes);
			if (compare > 0) {
				memmove(((char *) vec->vector) + (i * vec->num_bytes), var_two, vec->num_bytes);
				memmove(((char *) vec->vector) + (j * vec->num_bytes), var_one, vec->num_bytes);
			}
		}

	}
}
*/
// --------------------------------------------------------------------------------


void reverse_vector(Vector *vec) {
	int num = 0;
	int value;
	for (int i = vec->active_length - 1; i > 0; i--) {
		value = ((int *) vec->vector)[vec->active_length - 1];
		pop_vector(vec, vec->active_length - 1);
		insert_vector(vec, &value, 1, num);
		num++;
	}
}

// --------------------------------------------------------------------------------

float median_vector(Vector *vec) {
	float median;
	Vector sorted_vec = init_type_vector(vec->dat_type, vec->allocated_length);
	push_vector(&sorted_vec, vec->vector, vec->active_length);
	sort_vector(&sorted_vec, ASCENDING);
	if (sorted_vec.active_length % 2 == 0) {
		int median_1 = ((int *)sorted_vec.vector)[sorted_vec.active_length / 2];
		int median_2 = ((int *)sorted_vec.vector)[(sorted_vec.active_length - 1) / 2];
		float dat = ((float)median_1 + (float)median_2) / 2.0;
		return (float) dat;
	}
	else {
		printf("YES\n");
		size_t index = ((vec->active_length + 1) / 2) - 1;
		int dat = ((int *)sorted_vec.vector)[index];
		return (float) dat;
	}
}

// --------------------------------------------------------------------------------

int sum_vector(Vector *vec) {
	int sum = 0;
	for (int i = 0; i < vec->active_length; i++) {
		int add = ((int *)vec->vector)[i];
		sum += add;
	}
	return sum;
}

// --------------------------------------------------------------------------------

float average_vector(Vector *vec) {
	float avg;
	avg = (float) sum_vector(vec) / vec->active_length;
	return avg;
}

// --------------------------------------------------------------------------------


float stdev_vector(Vector *vec) {
	float stdev, average, var, var_sum, variance;
	int number;
	var_sum = 0;
	average = (float) sum_vector(vec) / vec->active_length;
	for (int i = 0; i < vec->active_length; i++) {
		number = ((int *)vec->vector)[i];
		var = pow(((float) number - average), 2.0f);
		var_sum += var;
	}
	variance = var_sum / vec->active_length;
	stdev = sqrt(variance);
	return stdev;
}
// --------------------------------------------------------------------------------

Vector cumsum_vector(Vector *vec) {
	Vector cumsum_vec = init_type_vector(vec->dat_type, vec->allocated_length);
	int sum = ((int *)vec->vector)[0];
	push_vector(&cumsum_vec, &sum, 1);
	for (int i = 1; i < vec->active_length; i++) {
		sum += ((int *)vec->vector)[i];
		push_vector(&cumsum_vec, &sum, 1);
	}
	return cumsum_vec;
}
// ================================================================================
// ================================================================================
// eof
