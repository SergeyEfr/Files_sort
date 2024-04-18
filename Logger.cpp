#include"Logger.h"
#include<fstream>

void Logger::printlog(vector<string>& arr_str, map <string, string>& type_storage, map<string, int>& byte_storage) {
    string write_path;
    cout << "Enter the path where to write the received information about the files: " << endl;
    cin >> write_path;
    ofstream out;
    out.open(write_path);
    vector <string>::iterator iter;

    if (out.is_open())
    {
        out << "List of file types: " << endl;
        for (const auto& element : type_storage) {
            out << "File " << element.first << " has type: " << element.second << endl;
        }

        for (iter = arr_str.begin(); iter != arr_str.end(); ++iter) {
            string line = *iter;
            out << "The most frequent byte in the file : " + line + ": " << hex << byte_storage[line] << endl;
            out << '\n';
        }
    }
    out.close();
}