#include"Logger.h"
#include<fstream>

void Logger::printlog(vector<string> &arr_str, map <string, string> &type_storage, map<string, int> &byte_storage) {
    string write_path;
    cout << "Enter the path where to write the received information about the files: " << endl;
    cin >> write_path;
    ofstream out;
    out.open(write_path);

    if (out.is_open())
    {
        out << "List of file types: " << endl;
        for (const auto &element : type_storage) {
            out << "File " << element.first << " has type: " << element.second << endl;
        }

        for (const string &line: arr_str) {

            out << "The most frequent byte in the file : " + line + ": " << hex << byte_storage[line] << endl;
            out << '\n';
        }
    }
    out.close();
}

void Logger::cipher_printlog(pair<string, string> &encrypted_files) {
    string write_path;
    string file_name = encrypted_files.first;
    string cipher_type = encrypted_files.second;
    cout << "Enter the path where to write the received information about the files: " << endl;
    cin >> write_path;
    ofstream out;
    out.open(write_path);

    if (out.is_open())
    {
        out << "File " << file_name << " is encrypted with " << cipher_type << endl;
        out << '\n';
    }
    out.close();
}