#include <iostream>
#include <vector>
#include <string>

int main()
{
    int occurences[255];

    std::string range;
    std::string character;
    std::string input;

    int successful_strings = 0;
    int positioned_strings = 0;

    while (std::cin >> range)
    {
        int min = stoi(range.substr(0, range.find("-")));
        int max = stoi(range.substr(range.find("-") + 1, range.length()));

        std::cin >> character;
        char chara = character.at(0);

        std::cin >> input;

        for (int i = 0; i < 255; i++)
        {
            occurences[i] = 0;
        }

        int pos = 0;
        bool has_found = false;
        for (char &c : input)
        {
            pos += 1;
            if (c == chara && (pos == min || pos == max))
            {
                has_found = !has_found;
            }
            occurences[c] += 1;
        }

        int count = occurences[chara];
        if (min <= count && count <= max)
        {
            successful_strings++;
        }

        if (has_found)
        {
            positioned_strings++;
        }
    }

    std::cout << "Part One" << std::endl;
    std::cout << successful_strings << std::endl;

    std::cout << "Part Two" << std::endl;
    std::cout << positioned_strings << std::endl;
}