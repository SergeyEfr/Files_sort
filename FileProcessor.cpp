#include"FileProcessor.h"
using namespace std;

void FileProcessor::store_file_types(CommandExecutor &obj2, const vector<string> &arr_str, const string &path) {
    cout << "The List of files in the got vector: " << endl;
    
    for ( const string &line: arr_str) {

        string command_2 = "file " + path + "/" + line;
        cout << "command_2: " << command_2 << endl;
        string file = obj2.execute(command_2);
        cout << file << endl;
        int idx = 0;
        int idx_end = 0;
        if (file.find(':') == string::npos) {
            continue;
        }
        else {
            idx = file.find(':');
        }

        if (file.find(',') == string::npos) {
            continue;
        }
        else {
            idx_end = file.find(',', idx);
        }
        idx = idx + 2;
        
        string file_type = file.substr(idx, idx_end - idx);
        type_storage[line] = file_type;

        if (find(__f_types.begin(), __f_types.end(), file_type) == __f_types.end()) {
            __f_types.push_back(file_type);
        }
        cout << "Type of file " << line << ": " << file_type << endl;
        cout << '\n';

    }
    cout << "All file types saved in the vector: " << endl;
    vector<string>::iterator iter;
    for (iter = __f_types.begin(); iter != __f_types.end(); ++iter) {
        cout << *iter << endl;
    }
}

void FileProcessor::files_sort(const string &path) {
    map <string, string> type_to_directory;
    for (const string &line: __f_types) {
        string s = line;
        replace(s.begin(), s.end(), ' ', '_');
  
        cout << "s: " + s << endl;
        string path_new_directory = path + "/" + s;
        type_to_directory[line] = path_new_directory;
        cout << "path_new_directory: " + path_new_directory << "\n" << endl;
        string command_3 = "mkdir " + path_new_directory;
        const char* command_3_char = command_3.c_str();
        system(command_3_char);
    }
    string type;
    for (const auto &element : type_storage) {

        type = element.second;
        string command_4 = "mv " + path + "/" + element.first + " " + type_to_directory[type];
        const char* command_4_char = command_4.c_str();
        system(command_4_char);

    }
}

vector<string> FileProcessor::get_file_names(const string& path, CommandExecutor &obj)
{
    vector<string> file_names;
    string command_1 = "ls " + path;
    cout << "command_1: " << command_1 << endl;
    string files_list = obj.execute(command_1);
    cout << "files_list: " << files_list << endl;

    char separator = '\n';
    
    string s;
    for (char c : files_list) {
        if (c != separator) {
            s += c;
        }

        else {

            file_names.push_back(s);
            s.clear();

        }
    }
    
    return file_names;
}

int FileProcessor::most_often_byte(const string &path) {
    string path_to_file = path;
    cout << "path_to_file: " << path_to_file << endl;
    unsigned char ch = ' '; //  тут будет байт
    vector<unsigned int> vbyte(256, 0); // индекс - код байта, содержимое - количество вхождений
    vector<unsigned int>::iterator v_iter;
    ifstream file2;
    file2.open(path_to_file, ios::in | ios::binary);
    if (file2.is_open()) {
        cout << "File was opend!" << endl;
    }
    else {
        cout << "File was not opend!" << endl;
    }
    while (file2.read((char*)&ch, 1))// считываем побайтно
    {
        vbyte[(unsigned int)ch]++;
        
    }
    file2.close();
    pair<unsigned int, int> result = { 0, 0 };
    
    int p = 0;
    for (unsigned int &num: vbyte) {
     
        if (result.first < num) {
            result = make_pair(num, p);
        }
        p++;
    }

    return result.second;
}
