// read file

#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::ifstream file("filename.txt"); // replace with your file name

    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
    return 0;
}


// Write file
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::ofstream file("filename.txt"); // replace with your file name

    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::string line = "This is a line to write to the file.";
    file << line << '\n';

    file.close();
    return 0;
}