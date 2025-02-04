#pragma once
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#define DEFAULT_ARRAY_ALLOCATED 4
#define DEFAULT_VALUE_INIT 1
using namespace std;
void v_EnlargeArrays(int **pi_values, int **pi_offsets, int *num_nondefault_values, int *arrays_size_allocated);
void v_ShortenArrays(int **pi_values, int **pi_offsets, int *num_nondefault_values, int *arrays_size_allocated);
void v_ReallocateArrays(int **pi_values, int **pi_offsets, int *num_nondefault_values, int *arrays_size_allocated);
void v_VectorDispose(int **pi_values, int **pi_offsets, bool *vector_exist);
string  s_ReturnStringRepresentation(int *pi_values, int *pi_offsets, int *num_nondefault_values, int *default_value, int *vector_length,
	bool *vector_exists);
int num_FindNumberInArray(int *tab, int value, int length);
void v_DeleteNumberFromArray(int *arrayToDelete, int indexToRemove, int length);
void v_SetVectorValue(int **pi_values, int **pi_offsets, int *num_nondefault_values, int *arrays_size_allocated, int *default_value, int value, int offset,
	int *vector_length, bool *vector_exists);
void v_MakeVector(int *vector_length, int *default_value, int length, int value, bool *vector_exist, int **pi_values, int **pi_offsets,
	int DEFAULT_ARRAY_SIZE_ALLOCATED, int *num_of_nondefault_values);
void v_DefineVectorDefaultValue(int *num_of_nondefault_values, int *default_value, int new_value);
void v_VectorDispose(int **pi_values, int **pi_offsets, bool *vector_exist);
bool b_HasVectorOnlyDefaultValues(int *num_of_nondefault_values);
void v_SetVectorLength(int *num_of_nondefault_values, int *default_value, int* vector_length, int newLength, int **pi_offsets,
	int **pi_values, bool *vector_exists, int *arrays_size_allocated);
int num_Get(int *num_nondefault_values, int *default_value, int *vector_length, int *pi_offsets, int *pi_values, int offset, bool *vector_exists);