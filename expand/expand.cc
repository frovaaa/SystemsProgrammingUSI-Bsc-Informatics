#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#include <vector>
#include <map>
#include <tuple>

#define ERROR_MESSAGE "invalid rules file f"
#define DEFAULT_RULES_FILE "RULES"

// p -> t
#define RULE_TYPE std::map<std::string, std::string>
RULE_TYPE rules;

// piece of text , already_used
#define WORD_PIECE std::tuple<std::string, bool>
std::vector<WORD_PIECE> text;

int add_rules(std::string fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << ERROR_MESSAGE << fileName << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    RULE_TYPE::iterator currentRule = rules.end();
    bool inserting_rule = false;

    while (std::getline(file, line))
    {
        // pattern matching
        auto column_pos = line.find(':');

        if (column_pos == 0)
        {
            // : at the start of the line
            // i need to continue

            // bad formatting - rule already present
            if (!inserting_rule)
                continue;

            std::string rest_of_rule = line.substr(1, line.length());
            (*currentRule).second += (rest_of_rule + "\n");
        }
        else
        {
            inserting_rule = false;

            std::string new_rule_key = line.substr(0, column_pos);
            auto ins = rules.insert({new_rule_key, ""});

            // rule already present, skip it
            if (!(ins.second))
            {
                inserting_rule = false;
                continue;
            }
            else
                inserting_rule = true;

            std::string rest_of_rule = line.substr(column_pos + 1, line.length());
            currentRule = ins.first;

            (*currentRule).second += (rest_of_rule + "\n");
        }
    }

    file.close();
    return EXIT_SUCCESS;
}

void read_input()
{
    char c;
    while (std::cin.get(c))
        text.push_back({std::string(1, c), false});
}

void process_text()
{
    for (auto rule : rules)
    {
        std::string rule_key = std::get<0>(rule);
        std::string rule_value = std::get<1>(rule);

        bool reading_word = true;
        int char_pos = 0;
        std::vector<WORD_PIECE>::iterator start_word;
        std::vector<WORD_PIECE>::iterator end_word;

        for (std::vector<WORD_PIECE>::iterator word = text.begin();
             word != text.end(); ++word)
        {
            start_word = word;

            // word not valid
            if (std::get<1>(*word))
            {
                reading_word = false;
                continue;
            }

            std::string current_word = std::get<0>(*word);
            if (char_pos < rule_key.length())
            {
                if (current_word[0] == rule_key[char_pos])
                {
                    // matching until now
                    reading_word = true;
                    end_word = word;
                }
                else
                {
                    reading_word = false;
                    start_word = word;
                    end_word = word;
                }
            }
            else
            {
                if (start_word == end_word)
                {
                    std::get<1>(*start_word) = true;
                    reading_word = false;
                    continue;
                }
                std::vector<WORD_PIECE>::iterator temp_pos = start_word;
                // finished word
                std::get<1>(*temp_pos) = true;
                ++temp_pos;
                while (temp_pos != end_word)
                {
                    std::get<0>(*start_word) += (std::get<0>(*temp_pos));
                    std::vector<WORD_PIECE>::iterator old = temp_pos;
                    ++temp_pos;
                    text.erase(old);
                }
            }
        }
    }
}

void print_text(){
    for(auto word : text){
        std::cout << std::get<0>(word);
    }
}

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        if (add_rules(DEFAULT_RULES_FILE) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    else
    {
        // read the rules files
        unsigned n_files = argc - 1;
        for (unsigned i = 0; i < n_files; ++i)
        {
            // Add the rules from the file
            if (add_rules(argv[i]) == EXIT_FAILURE)
                return EXIT_FAILURE;
        }
    }

    read_input();

    process_text();

    print_text();

    return EXIT_SUCCESS;
}
