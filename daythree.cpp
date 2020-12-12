#include <iostream>
#include <vector>
#include <string>

int main()
{
    const int RIGHT_DIRECTIONS[] = {1, 3, 5, 7, 1};
    const int DOWN_DIRECTIONS[] = {1, 1, 1, 1, 2};
    const int PART_ONE_INDEX = 1;

    int left_limit = 0;
    int bottom_limit = 0;

    std::vector<std::string> map(0);
    std::string input;

    while (std::cin >> input)
    {
        left_limit = input.length();
        map.push_back(input);
        bottom_limit++;
    }

    int trees_hit[5];
    for (int i = 0; i < 5; i++)
    {
        trees_hit[i] = 0;
    }

    for (int i = 0; i < 5; i++)
    {
        int horizontal_pos = 0;
        for (int y = 1; y < bottom_limit; y += DOWN_DIRECTIONS[i])
        {
            horizontal_pos = (horizontal_pos + RIGHT_DIRECTIONS[i]) % left_limit;

            char tile = map.at(y).at(horizontal_pos);
            if (tile == '#')
            {
                trees_hit[i]++;
            }
        }
    }
    std::cout << "Part One" << std::endl;
    std::cout << trees_hit[PART_ONE_INDEX] << std::endl;

    std::cout << "Part Two" << std::endl;
    long answer = 1;
    for (int i = 0; i < 5; i++)
    {
        answer *= trees_hit[i];
    }
    std::cout << answer << std::endl;
}