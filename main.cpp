
#include"CommandExecutor.h"
#include"FileProcessor.h"
#include"Logger.h"
#include<clocale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    string files_path;
    cout << "Введите путь до директории: " << endl;
    getline(cin, files_path);

    vector<string> file_names;
    vector<string>::iterator iter;

    CommandExecutor obj;
    file_names = FileProcessor::get_file_names(files_path, obj);

    FileProcessor file_processor;
    
    map<string, int> byte_storage;
    for (const string &line: file_names) {
        string file_path = files_path + "/" + line;
        int often_byte = file_processor.most_often_byte(file_path);
        byte_storage[line] = often_byte;
        cout << "Самый частый байт в файле : " + line + ": " << hex << byte_storage[line] << endl;
        cout << '\n';
    }

    file_processor.store_file_types(obj, file_names, files_path);
    file_processor.files_sort(files_path);
    map <string, string> t_storage = file_processor.type_storage;
    Logger obj_l;
    obj_l.printlog( file_names, t_storage, byte_storage);

    return 0;
}

