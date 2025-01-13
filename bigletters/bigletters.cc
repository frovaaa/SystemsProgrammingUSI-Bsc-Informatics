/**
 * @author Frova Davide
 * System Programming 2023-24 Final exam (18/01/2024)
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <vector>

#define DEFAULT_FONT_FILE "FONT"

class charFont
{
private:
    unsigned width;
    unsigned height;
    unsigned depth;
    // this will store the rappresentation of the big-char as string
    std::string v;

public:
    // Constructors
    charFont() : width(0), height(0) {}
    charFont(unsigned width, unsigned height, unsigned depth, std::string v) : width(width), height(height), depth(depth), v(v) {}
    charFont(const charFont &c) : width(c.width), height(c.height), depth(c.depth), v(c.v) {} // copy-constructor

    // Destructor
    ~charFont() {}

    // Methods
    unsigned getWidth()
    {
        return width;
    }

    unsigned getHeight()
    {
        return height;
    }

    unsigned getDepth()
    {
        return depth;
    }

    std::string getV()
    {
        return v;
    }
};

#define FONT_FAMILY_TYPE std::map<char, charFont> // maybe needed to do iterator
FONT_FAMILY_TYPE fontFamily;                      // Map from string to charFont
unsigned fontFamilyMaxHeight = 0;
unsigned fontFamilyMaxDepth = 0; // used when printing to determine the base-line height

// output vector of vectors (vov)
// I can still use vov[y][x] to access elements and get a reference to them
std::vector<std::vector<char>> vov;

int read_font_file(std::string fileName)
{
    // try to read file
    std::ifstream file(fileName);

    // check for error
    if (!file)
        return EXIT_FAILURE;

    // we can read line by line
    std::string line;
    while (std::getline(file, line))
    {
        // every line we will read the char, width and height

        auto column_pos = line.find(':'); // look for : char
        if (column_pos == line.npos)
        {
            // error, no : found, invalid file
            return EXIT_FAILURE;
        }

        char c;
        unsigned width;
        unsigned height;
        unsigned depth;
        std::string infoPart = line.substr(0, column_pos);

        // the format of the infoPart will always be followed, so no
        // need to check the format

        // save character
        c = infoPart[0];

        // to convert the values to integers:
        // get the single char using the string as an array
        // convert the single char in a string
        // (could do directly substr but it's easier this way)
        // then use std::stoi to convert it to int
        width = std::stoul(std::string(1, infoPart[2]));
        height = std::stoul(std::string(1, infoPart[4]));
        depth = std::stoul(std::string(1, infoPart[6]));

        // Now we read the part with the rappresentation

        std::string dataPart = line.substr(column_pos + 1, line.length());
        // check if line is correct length
        if (dataPart.length() != (width * height))
        {
            // invalid format, error
            return EXIT_FAILURE;
        }
        // correct format, save it in the charFont
        // create a new charFont with the values that we got
        charFont temp_cf(width, height, depth, dataPart);

        // Now we add the element to the map
        auto i = fontFamily.insert({c, temp_cf});
        if (!(i.second))
        {
            // couldn't add element to map, error bad format
            return EXIT_FAILURE;
        }

        // Check if the height is a new max height
        if ((height + depth) > fontFamilyMaxHeight)
            fontFamilyMaxHeight = (height + depth);

        // Check if the depth is a new max depth
        if (depth > fontFamilyMaxDepth)
            fontFamilyMaxDepth = depth;
    }

    // close file stream
    file.close();
    return EXIT_SUCCESS;
}

int process_input()
{
    unsigned baseLineY = fontFamilyMaxHeight - fontFamilyMaxDepth - 1;

    std::vector<char> emptyVector;
    // first fill the vov with empty vectors for the y
    for (unsigned y = 0; y < fontFamilyMaxHeight; ++y)
        vov.push_back(emptyVector);

    // we read char by char
    // foreach char we will check if it is in the map
    // then we will fill in the vov based on the definition of the font
    // empty spaces will be ' ' as every char will actually occupy
    // fontFamilyMaxHeight * charWidth

    // the overall x cursor position should be kept the same as
    // I always push back to every y of the vector
    char c;
    while (std::cin.get(c))
    {
        auto itr = fontFamily.find(' ');
        // check if not found
        if (itr == fontFamily.end())
        {
            // char not found, use standard format
            // c 1 1 0:c
            for (unsigned y = 0; y < fontFamilyMaxHeight; ++y)
            {
                // blank spaces unitl i reach the base-line, then i fill in again
                if (y == baseLineY)
                    vov[y].push_back(c);
                else
                    vov[y].push_back(' ');
            }

            // add line of spaces as separator
            for (unsigned y = 0; y < fontFamilyMaxHeight; ++y)
                vov[y].push_back(' ');
        }
        else
        {
            charFont &cf = (*itr).second;
            std::string value = cf.getV(); // get a copy
            // first i will need to add the spaces before and after the string
            // to match the max height
            unsigned totalToAddY = fontFamilyMaxHeight - cf.getHeight();
            if (totalToAddY != 0)
            {
                // need to add before or after based on the depth
                unsigned addAfter = fontFamilyMaxDepth - cf.getDepth();
                unsigned addBefore = totalToAddY - addAfter;

                // add the ones before
                for (unsigned i = 0; i < addBefore; ++i)
                    value = " " + value;

                // add after (after base line (down))
                for (unsigned i = 0; i < addAfter; ++i)
                    value += " ";
            }

            // then push everything in the vov
            for (unsigned y = 0; y < fontFamilyMaxHeight; ++y)
            {
                for (unsigned x = 0; x < cf.getWidth(); ++x)
                {
                    vov[y].push_back(value[x + y * cf.getWidth()]);
                }
            }
        }
    }

    return EXIT_SUCCESS;
}

void print_matrix()
{
    for (auto row : vov)
    {
        for (auto val : row)
        {
            std::cout << val;
        }
    }
}

int main(int argc, char const *argv[])
{
    std::string fontFileName;
    // no font-file name provided, using default one
    if (argc < 2)
        fontFileName = DEFAULT_FONT_FILE;
    else if (argc == 2)
    {
        // Font-file name provided
        fontFileName = argv[1];
    }
    else if (argc > 2)
    {
        // too many arguments, error
        return EXIT_FAILURE;
    }

    // now we read the font-file, check if it gives as error
    // parse the data into our dataStructure fontFamily
    if (read_font_file(fontFileName) == EXIT_FAILURE)
        return EXIT_FAILURE;

    // Now we can read the input data from the std in and process it
    // we check for errors
    if (process_input() == EXIT_FAILURE)
        return EXIT_FAILURE;

    // now print the final matix
    print_matrix();

    return EXIT_SUCCESS;
}