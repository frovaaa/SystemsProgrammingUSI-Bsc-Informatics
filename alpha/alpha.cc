#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>

#define DECODE_MODE true
#define ENCODE_MODE false

int encoding()
{
    std::string input;
    std::string temp_input = "";
    while (std::getline(std::cin, temp_input))
    {
        input += (temp_input + '\n');
    }

    // input = input.substr(0, input.length() - 1);

    std::string valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result = "";
    std::string hex = "abcdefghijklmnop";

    for (char c : input)
    {
        if (c < 0)
            return EXIT_FAILURE;

        if (valid_chars.find(c) == valid_chars.npos)
        {
            // char not found
            // special encoding HEX
            int most = c / 16;
            int least = c % 16;
            result += "Q";
            result += hex[most];
            result += hex[least];
        }
        else
        {
            if (c == 'Q')
                result += "QQ";
            else
                result += c;
        }
    }

    for (unsigned i = 0; i < result.length(); ++i)
    {
        if (i != 0 && i % 80 == 0)
            std::cout << std::endl;
        std::cout << result[i];
    }

    if (result.length() != 0)
        std::cout << std::endl;

    return EXIT_SUCCESS;
}

// Invalid code -> return EXIT_FAILURE
int deconding()
{
    std::string input;
    std::string temp_input = "";
    while (std::getline(std::cin, temp_input))
    {
        input += temp_input;
    }

    std::string result = "";
    std::string hex = "abcdefghijklmnop";
    std::string valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // 0: not decoding
    // 1: Read Q
    // 2: Read c1
    // 3: Read c2
    int decoding = 0;
    char c1 = 0;
    char c2 = 0;

    for (char c : input)
    {
        if (c < 0)
            return EXIT_FAILURE;

        if (valid_chars.find(c) == valid_chars.npos)
            continue;
        else
        {
            switch (decoding)
            {
            case 0:
                decoding = 1;
                continue;
                break;
            case 1:
                c1 = c;
                decoding = 2;
                continue;
                break;
            case 2:
                c2 = c;
                decoding = 3;
                continue;
                break;
            case 3:
            {
                auto c1_val = hex.find(c1);
                if (c1_val == hex.npos)
                    return EXIT_FAILURE;

                auto c2_val = hex.find(c2);
                if (c2_val == hex.npos)
                    return EXIT_FAILURE;

                c1 = 0;
                c2 = 0;

                char res = (16 * c1_val) + c2_val;

                result += res;
                continue;
                break;
            }
            default:
                return EXIT_FAILURE;
                break;
            }

            // not special
            result += c;
        }
    }

    for (unsigned i = 0; i < result.length(); ++i)
    {
        if (i != 0 && i % 80 == 0)
            std::cout << std::endl;
        std::cout << result[i];
    }

    if (result.length() != 0)
        std::cout << std::endl;

    return EXIT_SUCCESS;
}

int main(int argc, char const *argv[])
{
    std::string flag = "-d";

    if (argc < 2)
    {
        return encoding();
    }
    else if (argc == 2 && flag.compare(argv[1]) == 0)
    {
        return deconding();
    }
    else
    {
        return EXIT_FAILURE;
    }

    return EXIT_FAILURE;
}
