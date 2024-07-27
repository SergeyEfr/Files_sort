
#include"CommandExecutor.h"
#include"FileProcessor.h"
#include"Logger.h"
#include<clocale>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Number of parameters: " << argc << endl;
    if (argc == 1)
    {
        cout << "Usage: ./linux2.out [sort/xor_encrypt/xor_decrypt/bit_encrypt/bit_decrypt]" << endl;
    }
    string arg = argv[1];
    if (arg == "sort") 
    {
        FileProcessor::sort_actions();
        
    }
    else if (arg == "xor_encrypt")
    {
        FileProcessor::xor_cipher_actions();
    }
    else if (arg == "xor_decrypt")
    {
        FileProcessor::xor_decipher_actions();
    }
    else if (arg == "bit_encrypt")
    {
        FileProcessor::bit_cipher_actions();
    }
    else if (arg == "bit_decrypt")
    {   
        FileProcessor::bit_decipher_actions();
    }
    else
    {
        cerr << "Unknown mode: " << arg << endl;
    }
    return 0;
}

