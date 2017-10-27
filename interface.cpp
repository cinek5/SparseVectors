
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include "interface.h"
using namespace std;
string  s_handleSingleInput() {
	string inputLine;
	getline(cin, inputLine);
	for (string::size_type i = 0; i < inputLine.length(); i++)
	{
		inputLine[i] = toupper(inputLine[i]);
	} 
	vector<string> slicedCommands = s_sliceCommand(inputLine);
   
	return inputLine;
}
bool b_checkCommand(vector<string>& slicedCommands) {
	map<string, int>::iterator it;
	map<string, int>  numOfArgsMap;
	numOfArgsMap["mvec"] = 3;
	numOfArgsMap["def"] = 3;
	numOfArgsMap["get"] = 2;
	numOfArgsMap["len"] = 2;
	numOfArgsMap["print"] = 1;
	numOfArgsMap["del"] = 1;
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
	
	vector<string>  tokens = s_sliceCommand("get 23 ");
	
	for (unsigned i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << endl;
	}
	cout << b_checkCommand(tokens) << endl;
	
	 
	system("pause");

    return 0;
}