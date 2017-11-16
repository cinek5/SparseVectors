
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include "interface.h"
#include "ZMPO1.h"

 
using namespace std;
void  v_handleSingleInput(int *arrays_size_allocated,int *vector_length, bool *vector_exist,
	int *default_value, int *num_nondefault_values, int **pi_values, int **pi_offsets ) {

	string inputLine;	
	getline(cin, inputLine);
	map<string, int>  commandsMap;
	commandsMap["MVEC"] = 0;
	commandsMap["DEF"] = 1;
	commandsMap["GET"] = 2;
	commandsMap["LEN"] = 3;
	commandsMap["PRINT"] = 4;
	commandsMap["DEL"] = 5;
	for (string::size_type i = 0; i < inputLine.length(); i++)
	{
		inputLine[i] = toupper(inputLine[i]);
	} 
	vector<string> slicedCommands = s_sliceCommand(inputLine);
	string command = slicedCommands[0];
   if (b_checkCommand(slicedCommands)) {
	   switch (commandsMap[command]) {
	   case 0: 
		   //mvec
		   v_MakeVector(vector_length, default_value, stoi(slicedCommands[1]), stoi(slicedCommands[2]), vector_exist, pi_values, pi_offsets, DEFAULT_ARRAY_ALLOCATED,
			   num_nondefault_values);
		   break;
	   case 1: 
		   //def
		   v_SetVectorValue(pi_values, pi_offsets, num_nondefault_values, arrays_size_allocated, default_value, stoi(slicedCommands[2]),
			   stoi(slicedCommands[1]),vector_length,vector_exist);
		   break;
	   case 2:
		   //get
		   cout << num_Get(num_nondefault_values, default_value, vector_length, *pi_offsets, *pi_values, stoi(slicedCommands[1]), vector_exist)<<endl;
		   break;
	   case 3:
		   //len 
		   v_SetVectorLength(num_nondefault_values, default_value, vector_length, stoi(slicedCommands[1]), pi_offsets,pi_values,vector_exist,arrays_size_allocated);
		   break;
	   case 4:
		   //print
		   cout << s_ReturnStringRepresentation(*pi_values,*pi_offsets,num_nondefault_values,default_value,vector_length,vector_exist) << endl;
		   break;
	   case 5:
		   v_VectorDispose(pi_values, pi_offsets, vector_exist);
		   break;

	  

		}
   }
   else {
	   cout << "WRONG COMMAND, TRY AGAIN" << endl;
   }


   

}
bool b_checkCommand(vector<string>& slicedCommands) {
	map<string, int>::iterator it;
	map<string, int>  numOfArgsMap;
	numOfArgsMap["MVEC"] = 3;
	numOfArgsMap["DEF"] = 3;
	numOfArgsMap["GET"] = 2;
	numOfArgsMap["LEN"] = 2;
	numOfArgsMap["PRINT"] = 1;
	numOfArgsMap["DEL"] = 1;
	string command = slicedCommands[0];
	it = numOfArgsMap.find(command);
	if (it != numOfArgsMap.end()) {
		return b_checkArguments(numOfArgsMap[command], slicedCommands);
	}

	
	 
	return false;
}
bool b_checkArguments(int numberOfArguments, vector<string>& slicedCommands) {
	if (slicedCommands.size() != numberOfArguments) return false;
	for (unsigned i = 1; i < slicedCommands.size(); i++) {
		if (!is_number(slicedCommands[i])) return false;
	}
	return true;
}
bool is_number(std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

vector<string> s_sliceCommand(string str) {
	vector<string> result;
	size_t pos = 0;
	string delimiter;
	delimiter = " ";
	while ((pos = str.find(delimiter)) != std::string::npos) {
		string token;
		token = str.substr(0, pos);
		str.erase(0, pos + delimiter.length());
		if (token.length()>0) result.push_back(token);
	}
	if (str!=" " && str!="") result.push_back(str);
	return result;
}
int main(){
	
	int arrays_size_allocated = DEFAULT_ARRAY_ALLOCATED;
	int vector_length; // dlugosc wektora
	bool vector_exist = false;
	int default_value = DEFAULT_VALUE_INIT;
	int num_nondefault_values; // number of values which are not default ( it's also the length of pi_values and pi_offsets arrays ) 
	int *pi_values;
	int *pi_offsets;

	while (true) {
		v_handleSingleInput(&arrays_size_allocated,&vector_length,&vector_exist,&default_value,&num_nondefault_values,&pi_values,&pi_offsets);
	}
	
	system("pause");

    return 0;
}