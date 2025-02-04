// ZMPO1.cpp : Defines the entry point for the console application.
//

#include "ZMPO1.h"
#include "stdafx.h"

void v_EnlargeArrays(int **pi_values, int **pi_offsets, int *num_nondefault_values, int *arrays_size_allocated) {
	 *arrays_size_allocated *= 2;
	 v_ReallocateArrays(pi_values, pi_offsets, num_nondefault_values, arrays_size_allocated);

}
void v_ReallocateArrays(int **pi_values, int **pi_offsets, int *num_nondefault_values, int *arrays_size_allocated) {
	int *new_pi_values = new int[*arrays_size_allocated];
	int *new_pi_offsets = new int[*arrays_size_allocated];
	for (int i = 0; i < *num_nondefault_values; i++) {
		new_pi_values[i] = (*pi_values)[i];
		new_pi_offsets[i] = (*pi_offsets)[i];
	}
	delete *pi_values;
	delete *pi_offsets;
	*pi_values = new_pi_values;
	*pi_offsets = new_pi_offsets;
}

void v_ShortenArrays(int **pi_values, int **pi_offsets, int *num_nondefault_values, int *arrays_size_allocated) {
	*arrays_size_allocated *= (3 / 4);
	v_ReallocateArrays(pi_values, pi_offsets, num_nondefault_values, arrays_size_allocated);
	
}

string  s_ReturnStringRepresentation(int *pi_values, int *pi_offsets, int *num_nondefault_values, int *default_value, int *vector_length,
	bool *vector_exist) {
	string s_representation;
	if (*vector_exist) {
		
		s_representation = "len: " + to_string(*vector_length) + " values: ";

		int currentOffset = 0;
		for (int i = 0; i < *vector_length; i++) {
			if (currentOffset < *num_nondefault_values && pi_offsets[currentOffset] == i) {
				s_representation += to_string(pi_values[currentOffset]) + (i == *vector_length - 1 ? " " : ",");
				currentOffset++;

			}
			else {
				s_representation += to_string(*default_value) + (i == *vector_length - 1 ? " " : ",");
			}
		}
	}
	else {
		cout << "error : VECTOR DOESN'T EXIST" << endl;
	}
	
	
	return s_representation;
	
}
int num_FindNumberInArray(int *tab, int value,int length) {
	int indexToRemove = -1;
	int i = 0;
	bool found = false;
	while (i < length && !found) {

		if (tab[i] == value) {
			found = true;
			indexToRemove = i;
		}

		i++;
	}
	
	return indexToRemove;
}
// deletes number from array but not change the size of the array in memory 
void v_DeleteNumberFromArray(int *arrayToDelete, int indexToRemove, int length) {
	for (int i = indexToRemove; i < length-1; i++) {
		arrayToDelete[i] = arrayToDelete[i + 1];
	}
}


void v_SetVectorValue(int **pi_values, int **pi_offsets, int *num_nondefault_values,int *arrays_size_allocated,int *default_value,int value, int offset, int *vector_length,bool *vector_exist) {
	if (offset >= 0 && offset < *vector_length && *vector_exist) {
		if (*num_nondefault_values + 1 > *arrays_size_allocated && value != *default_value) {
			// reallocate array if it's too small
			v_EnlargeArrays(pi_values, pi_offsets, num_nondefault_values, arrays_size_allocated);
		}
	

		if (*num_nondefault_values == 0 && value != *default_value) {
			// first non default value added
			(*pi_values)[0] = value;
			(*pi_offsets)[0] = offset;
			*num_nondefault_values += 1;

		}
		else {
			if (value != *default_value) {
				// check if there is already a non default value in this position
				int indexOfSocket = num_FindNumberInArray(*pi_offsets, offset, *num_nondefault_values);
				if (indexOfSocket != -1) { // then overwrite it
					(*pi_values)[indexOfSocket] = value;
				} // else insert new element
				else {
					int i = *num_nondefault_values;
					while (i > 0 && (*pi_offsets)[i - 1] > offset) {
						(*pi_offsets)[i] = (*pi_offsets)[i - 1];
						(*pi_values)[i] = (*pi_values)[i - 1];
						i--;
					}


(*pi_values)[i] = value;
(*pi_offsets)[i] = offset;
*num_nondefault_values += 1;


				}

			} // else value is default and maybe deletion is needed
			else {
				//check if there's element under offset and delete it
				int indexToRemove = num_FindNumberInArray(*pi_offsets, offset, *num_nondefault_values);

				if (indexToRemove != -1) {
					v_DeleteNumberFromArray(*pi_offsets, indexToRemove, *num_nondefault_values);
					v_DeleteNumberFromArray(*pi_values, indexToRemove, *num_nondefault_values);
					*num_nondefault_values -= 1;

				}
				if (*arrays_size_allocated >= *num_nondefault_values * 2)
					v_ShortenArrays(pi_values, pi_offsets, num_nondefault_values, arrays_size_allocated);

			}


		}
	}
	else {
		cout << "error: WRONG_OFFSET or VECTOR DOESN'T EXIST" << endl;
	}
}


void v_MakeVector(int *vector_length, int *default_value, int length, int value, bool *vector_exist, int **pi_values, int **pi_offsets,
	int DEFAULT_ARRAY_SIZE_ALLOCATED, int *num_of_nondefault_values) {
	if (*vector_exist) {
		v_VectorDispose(pi_values, pi_offsets, vector_exist);
	}

	*vector_length = length;
	*default_value = value;
	*num_of_nondefault_values = 0;
	*pi_values = new int[DEFAULT_ARRAY_SIZE_ALLOCATED];
	*pi_offsets = new int[DEFAULT_ARRAY_SIZE_ALLOCATED];

	*vector_exist = true;

}
void v_DefineVectorDefaultValue(int *num_of_nondefault_values, int *default_value, int new_value) {
	if (b_HasVectorOnlyDefaultValues(num_of_nondefault_values)) {
		*default_value = new_value;
	}
	else {
		cout << "can't do this, vector has values other than default";
	}

}
void v_VectorDispose(int **pi_values, int **pi_offsets, bool *vector_exist) {
	delete *pi_values;
	delete *pi_offsets;
	*vector_exist = false;
}

bool b_HasVectorOnlyDefaultValues(int *num_of_nondefault_values) {
	if (num_of_nondefault_values == 0) return true; else return false;
}
void v_SetVectorLength(int *num_of_nondefault_values, int *default_value, int* vector_length, int newLength, int  **pi_offsets, int **pi_values
	, bool *vector_exist, int *arrays_size_allocated) {
	if (*vector_exist) {
		while (*num_of_nondefault_values >= 0 && (*pi_offsets)[*num_of_nondefault_values] > newLength) {
			*num_of_nondefault_values--;
		} // cut vector values whose offset is more than newLength
		*vector_length = newLength; //sets new length

		if (*arrays_size_allocated >= *num_of_nondefault_values * 2) {
			v_ShortenArrays(pi_values, pi_offsets, num_of_nondefault_values, arrays_size_allocated);
		}
	}
	else {
		cout << "error: VECTOR DOESN'T EXIST" << endl;
	}
}
int num_Get(int *num_nondefault_values, int *default_value, int *vector_length, int *pi_offsets, int *pi_values, int offset, bool *vector_exists) {
	if (*vector_exists && offset >= 0 && offset < *vector_length) {
		if (*num_nondefault_values = 0) return *default_value;
		else {
			int index = num_FindNumberInArray(pi_offsets, offset, *vector_length);
			if (index == -1) return *default_value; else return pi_values[index];

		}

	}
	else {
		cout << "error: WRONG OFFSET OR VECTOR DOESN'T EXIST" << endl;
		return -1;
	}
}
void v_SwapValues(int *default_value, int *pi_offsets, int *pi_values, int *vector_length, int *num_nondefault_values) {
	if (*num_nondefault_values != 0) {
		if (*num_nondefault_values < 2) { // 1 wartosc domyslna
			if (pi_offsets[0] == 0) {
				pi_offsets[0] = *vector_length - 1;
			}
			else if (pi_offsets[0] == *vector_length - 1) {
				pi_offsets[0] = 0;
			}
		}
		else {
			if (pi_offsets[0] == 0 && pi_offsets[*num_nondefault_values - 1] == *vector_length - 1) {
				int help = pi_values[0];
				pi_values[0] = pi_values[*num_nondefault_values - 1];
				pi_values[*num_nondefault_values - 1] = help;

			}
			else {
				if (pi_offsets[0] == 0) {
					int help = pi_values[0];
					for (int i = 0; i < *num_nondefault_values - 1; i++) {
						pi_offsets[i] = pi_offsets[i + 1];
						pi_values[i] = pi_values[i + 1];

					}
					pi_offsets[*num_nondefault_values - 1] = *vector_length - 1;
					pi_values[*num_nondefault_values - 1] = help;
				}
				if (pi_offsets[*num_nondefault_values - 1] == *vector_length - 1) {
					int help = pi_values[*num_nondefault_values - 1];
					for (int i = *num_nondefault_values - 1; i > 0; i--) {
						pi_offsets[i] = pi_offsets[i - 1];
						pi_values[i] = pi_values[i - 1];

					}
					pi_offsets[0] = 0;
					pi_values[0] = help;
				}

			}
		}


	}

}
/*
int main()
{   
	const int DEFAULT_ARRAY_SIZE_ALLOCATED= 4;
	const int DEFAULT_VECTOR_LENGTH = 50;
	int arrays_size_allocated = DEFAULT_ARRAY_SIZE_ALLOCATED;
    int vector_length; // dlugosc wektora
	bool vector_exist = false;
    int default_value = 1;
	int num_nondefault_values; // number of values which are not default ( it's also the length of pi_values and pi_offsets arrays ) 
	int *pi_values;
	int *pi_offsets; 
	// test
	v_MakeVector(&vector_length, &default_value, 10, 1, &vector_exist, &pi_values, &pi_offsets, DEFAULT_ARRAY_SIZE_ALLOCATED , &num_nondefault_values);
	v_SetVectorValue(&pi_values, &pi_offsets, &num_nondefault_values, &arrays_size_allocated, &default_value, 8, 3);
	v_SetVectorValue(&pi_values, &pi_offsets, &num_nondefault_values, &arrays_size_allocated, &default_value, 5, 3);
	v_SetVectorValue(&pi_values, &pi_offsets, &num_nondefault_values, &arrays_size_allocated, &default_value,4, 2);
	v_SetVectorValue(&pi_values, &pi_offsets, &num_nondefault_values, &arrays_size_allocated, &default_value, 6, 7);
	v_SetVectorValue(&pi_values, &pi_offsets, &num_nondefault_values, &arrays_size_allocated, &default_value, 9, 8);
	v_SetVectorValue(&pi_values, &pi_offsets, &num_nondefault_values, &arrays_size_allocated, &default_value, 2, 9);
	string s_representation = s_ReturnStringRepresentation(pi_values, pi_offsets, &num_nondefault_values, &default_value, &vector_length);
	cout << s_representation << "\n";

	delete pi_values;
	delete pi_offsets;
	

	system("pause");

    return 0;
}

*/