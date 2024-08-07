#pragma once
#include"CommandExecutor.h"
#include"Logger.h"
#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
#include<fstream>
#include<bitset>

class FileProcessor {
public:
    static int most_often_byte(const string &path);
    static void file_cipher(const string &path_read, const string &path_write, char key);
    static void file_bit_cipher(const string& path_read, const string& path_write, int sh);
    static void file_bit_decipher(const string& path_read, const string& path_write, int sh);
    static void sort_actions();
    static void xor_cipher_actions();
    static void xor_decipher_actions();
    static void bit_cipher_actions();
    static void bit_decipher_actions();
    void store_file_types( const vector<string> &arr_str, const string &path);
    void files_sort(const string &path);
    map <string, string> type_storage;
    static vector<string> get_file_names(const string& path);
    
private:
    vector<string> __f_types;
    
};
