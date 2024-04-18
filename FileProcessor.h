#pragma once
#include"CommandExecutor.h";
#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
#include<fstream>

class FileProcessor {
public:
    int most_often_byte(string path);
    void store_file_types(CommandExecutor& obj2, vector<string>& arr_str, string path);
    void files_sort(string path);
    map <string, string> type_storage;
private:
    vector<string>f_types;
    vector <string>::iterator iter;
    map <string, string> type_to_directory;
    
};
