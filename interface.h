#pragma once
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

void  v_handleSingleInput(int *arrays_size_allocated, int *vector_length, bool *vector_exist,
	int *default_value, int *num_nondefault_values, int **pi_values, int **pi_offsets);
vector<string> s_sliceCommand(string str);
bool b_checkArguments(int numberOfArguments, vector<string>& slicedCommands);
bool b_checkCommand(vector<string>& slicedCommands);
bool is_number(string& s);
