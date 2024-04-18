
#include"CommandExecutor.h"
#include"FileProcessor.h"
#include"Logger.h"
#include<clocale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    string path;
    cout << "Введите путь до директории: " << endl;
    getline(cin, path);
    
    string command_1 = "ls " + path;
    cout << "command_1: " << command_1 << endl;
    CommandExecutor obj;
    string file = obj.execute(command_1);
    cout <<"file: "<< file << endl;

    vector<string> arr_str;
    vector<string>::iterator iter;
    char separator = '\n';
    int i = 0;
    string s;
    
    while (file[i] != '\0') {
        if (file[i] != separator) {
            s += file[i];
        }
        
        else {
            arr_str.push_back(s);
            s.clear();

        }
        
        i++;
        
    }
    
    FileProcessor obj_t;
    map<string, int> byte_storage;
    for (iter = arr_str.begin(); iter != arr_str.end(); ++iter) {
        string line = *iter;
        string file_path = path + "/" + line;
        int often_byte = obj_t.most_often_byte(file_path);
        byte_storage[line] = often_byte;

    }

    for (iter = arr_str.begin(); iter != arr_str.end(); ++iter) {
        string line = *iter;
        cout << "Самый частый байт в файле : " + line + ": " << hex << byte_storage[line] << endl;
        cout << '\n';
    }
    
    obj_t.store_file_types(obj, arr_str, path);
    obj_t.files_sort(path);
    map <string, string> t_storage = obj_t.type_storage;
    Logger obj_l;
    obj_l.printlog( arr_str, t_storage, byte_storage);

    return 0;
}

