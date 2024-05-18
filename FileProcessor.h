#pragma once
#include"CommandExecutor.h";
#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
#include<fstream>

class FileProcessor {
public:
    static int most_often_byte(const string &path);
    void store_file_types(CommandExecutor &obj2, const vector<string> &arr_str, const string &path);
    void files_sort(const string &path);
    map <string, string> type_storage;
    static vector<string> get_file_names(const string& path, CommandExecutor &obj);
    
private:
    vector<string> __f_types;
    
};
