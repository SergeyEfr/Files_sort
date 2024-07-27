#include"CommandExecutor.h"
#include <string>
#include<array>

using namespace std;

string CommandExecutor::execute(const string &command) {
    array<char, 128> buffer;
    string result;

    // Open pipe to file
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }

    // read till end of process:
    while (!feof(pipe)) {

        // use buffer to read and add to result
        if (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        {
            result += buffer.data();
        }
            
    }

    pclose(pipe);
    return result;
}

