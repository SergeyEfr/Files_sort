#pragma once
#include<vector>
#include<map>
#include<string>
#include<iostream>
using namespace std;

class Logger {
public:
	void printlog(vector<string>& arr_str, map <string, string>& type_storage, map<string, int>& byte_storage);
};
