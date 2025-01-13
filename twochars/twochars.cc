#include <iostream>
#include <ctype.h>
#include <string>

std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char const *argv[])
{
    int matrix[26][26];
    for (unsigned y = 0; y < 26; ++y)
        for (unsigned x = 0; x < 26; ++x)
            matrix[y][x] = -1;

    char prev = 0;
    char current;
    while (std::cin >> current)
    {
        if (islower(current))
            current = toupper(current);

        if (isupper(prev) && isupper(current))
        {
            if (matrix[prev - 'A'][current - 'A'] == -1)
                matrix[prev - 'A'][current - 'A'] = 0;
            matrix[prev - 'A'][current - 'A']++;
        }

        prev = current;
    }

    // look for max
    for (unsigned y = 0; y < 26; ++y)
    {
        int max = -1;
        for (unsigned x = 0; x < 26; ++x)
        {
            if (matrix[y][x] > max)
                max = matrix[y][x];
        }
        matrix[y][0] = max;
    }

    for (unsigned y = 0; y < 26; ++y)
    {
        if (matrix[y][0] == -1)
            continue;
        char current = y + 'A';
        char value = matrix[y][0] + 'A';
        std::cout << current << value << std::endl;
    }

    return 0;
}
