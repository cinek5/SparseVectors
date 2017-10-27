#pragma once
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

string  s_handleSingleInput(); //returns array 
vector<string> s_sliceCommand(string str);
bool b_checkArguments(int numberOfArguments, vector<string>& slicedCommands);
bool b_checkCommand(vector<string>& slicedCommands);
bool is_number(std::string& s);
