#include"FileProcessor.h"

using namespace std;

void FileProcessor::store_file_types( const vector<string> &arr_str, const string &path) {
    cout << "The List of files in the got vector: " << endl;
    
    for ( const string &line: arr_str) {
        string command_2 = "file ";

        command_2.append(path).append("/").append(line);
        cout << "command_2: " << command_2 << endl;
        string file = CommandExecutor::execute(command_2);
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
        string path_new_directory = path;
        path_new_directory.append("/").append(s);
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

vector<string> FileProcessor::get_file_names(const string &path)
{
    vector<string> file_names;
    string command_1 = "ls " + path;
    cout << "command_1: " << command_1 << endl;
    string files_list = CommandExecutor::execute(command_1);
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
    cout << "path_to_file: " << path << endl;
    unsigned char ch = ' '; //  тут будет байт
    vector<unsigned int> vbyte(256, 0); // индекс - код байта, содержимое - количество вхождений
    ifstream file2;
    file2.open(path, ios::in | ios::binary);
    if (file2.is_open()) {
        cout << "File was opend!" << endl;
    }
    else {
        cout << "File was not opend!" << endl;
    }
    while (file2.read((char*)&ch, 1)) // считываем побайтно
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

void FileProcessor::sort_actions()
{
    setlocale(LC_ALL, "");
    string files_path;
    cout << "Enter the to directory: " << endl;
    cin >> files_path;
    cout << "\n";
    vector<string> file_names;
    file_names = FileProcessor::get_file_names(files_path);
    FileProcessor file_processor;

    map<string, int> byte_storage;
    for (const string& line : file_names) {
        string file_path = files_path;
        file_path.append("/").append(line);
        int often_byte = file_processor.most_often_byte(file_path);
        byte_storage[line] = often_byte;
        cout << "The most frequent byte in the file : " + line + ": " << hex << byte_storage[line] << endl;
        cout << '\n';
    }

    file_processor.store_file_types(file_names, files_path);
    file_processor.files_sort(files_path);
    map <string, string> t_storage = file_processor.type_storage;
    
    Logger::printlog(file_names, t_storage, byte_storage);
}

void FileProcessor::file_cipher(const string &path_read, const string &path_write, char key) {
    
    ifstream in(path_read, ios::binary | ios::in);
    if (in.is_open()) {
        cout << "File was opend!" << endl;
    }
    else {
        cout << "File was not opend!" << endl;
    }

    ofstream out(path_write, ios::binary | ios::out);
    if (out.is_open()) {
        cout << "File was opend!" << endl;
    }
    else {
        cout << "File was not opend!" << endl;
    }
    char Key = key;
    char ch = ' ';
    while (in.read((char*) &ch, 1))// считываем побайтно
    {
        ch = ch ^ Key;
        out.write((char*) &ch, 1);
    }
    in.close();
    out.close();
}

void FileProcessor::xor_cipher_actions()
{
    string path_to_read;
    string path_to_write;
    char key;
    FileProcessor file_processor;
    cout << "Enter the path to the file you want to encrypt : " << endl;
    cin >> path_to_read;
    cout << "Enter the path to the file where you want to write the encrypted file: " << endl;
    cin >> path_to_write;
    cout << "Enter the key for xor cipher: " << endl;
    cin >> key;
    file_processor.file_cipher(path_to_read, path_to_write, key);
    pair<string, string> encrypted_storage = {path_to_read, "xor"};
    Logger::cipher_printlog(encrypted_storage);
}

void FileProcessor::xor_decipher_actions()
{
    string path_to_read;
    string path_to_write;
    char key;
    FileProcessor file_processor;
    cout << "Enter the path to the file you want to decrypt: " << endl;
    cin >> path_to_read;
    cout << "Enter the path to the file where you want to write the decrypted file: " << endl;
    cin >> path_to_write;
    cout << "Enter the key for xor decipher: " << endl;
    cin >> key;
    file_processor.file_cipher(path_to_read, path_to_write, key);
}

void FileProcessor::bit_cipher_actions()
{
    string path_to_read;
    string path_to_write;
    int shift_bits;
    cout << "Enter the path to the file you want to encrypt : " << endl;
    cin >> path_to_read;
    cout << "Enter the path to the file where you want to write the encrypted file: " << endl;
    cin >> path_to_write;
    cout << "Enter the shift of bits: " << endl;
    cin >> shift_bits;
    FileProcessor::file_bit_cipher(path_to_read, path_to_write, shift_bits);
    pair<string, string> encrypted_storage = { path_to_read, "bit_shift" };
    Logger::cipher_printlog(encrypted_storage);
}

void FileProcessor::bit_decipher_actions()
{
    string path_to_read;
    string path_to_write;
    int shift_bits;
    cout << "Enter the path to the file you want to decrypt: " << endl;
    cin >> path_to_read;
    cout << "Enter the path to the file where you want to write the decrypted file: " << endl;
    cin >> path_to_write;
    cout << "Enter the shift of bits: " << endl;
    cin >> shift_bits;
    FileProcessor::file_bit_decipher(path_to_read, path_to_write, shift_bits);
}

void FileProcessor::file_bit_cipher(const string& path_read, const string& path_write, int sh)
{
    ifstream in(path_read, ios::binary | ios::in);
    if (in.is_open()) {
        cout << "File was opend!" << endl;
    }
    else {
        cout << "File was not opend!" << endl;
    }

    ofstream out(path_write, ios::binary | ios::out);
    if (out.is_open()) {
        cout << "File was opend!" << endl;
    }
    else {
        cout << "File was not opend!" << endl;
    }
    
    char ch = ' ';
    while (in.read((char*)&ch, 1))// считываем побайтно
    {
        uint8_t byte = uint8_t(ch); // значение байта
        int shift = sh; // значение сдвига
        shift = shift % 8; // сдвиг не должен быть больше 8
       
        // Шифрование (циклический сдвиг влево)
        byte = (byte << shift) | (byte >> (8 - shift));
        ch = char(byte);
        
        out.write((char*)&ch, 1);
    }
    
    in.close();
    out.close();

};


void FileProcessor::file_bit_decipher(const string& path_read, const string& path_write, int sh)
{
    string file_for_write = path_write;
    string file_for_read = path_read;
    
    ifstream in(file_for_read, ios::binary | ios::in);
    if (in.is_open()) {
        cout << "File was opend!" << endl;
    }
    else {
        cout << "File was not opend!" << endl;
    }

    ofstream out(file_for_write, ios::binary | ios::out);
    if (out.is_open()) {
        cout << "File was opend!" << endl;
    }
    else {
        cout << "File was not opend!" << endl;
    }

    char ch = ' ';
    while (in.read((char*)&ch, 1))// считываем побайтно
    {
        uint8_t byte = uint8_t(ch); // значение байта
        int shift = sh; // значение сдвига
        shift = shift % 8; // сдвиг не должен быть больше 8
        
        // Дешифрование (циклический сдвиг вправо)
        byte = (byte >> shift) | (byte << (8 - shift));
        ch = char(byte);
        
        out.write((char*)&ch, 1);
    }

    in.close();
    out.close();

};

