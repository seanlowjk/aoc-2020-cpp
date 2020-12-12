#include <iostream>
#include <vector>

int main()
{
    const int desired_sum = 2020; 
    std::vector<int> inputs(0); 

    int input; 

    while (std::cin >> input)
    {
        inputs.push_back(input);
    }

    int len = inputs.size();

    std::cout << "Part One" << std::endl;

    for (int i = 0; i < len; i++) 
    {
        int first = inputs.at(i); 
        for (int j = i + 1; j < len; j++) 
        {
            int second = inputs.at(j); 
            if (first + second == desired_sum)
            {
                std::cout << first * second << std::endl;
            }
        }
    }

    std::cout << "Part Two" << std::endl;

    for (int i = 0; i < len; i++) 
    {
        int first = inputs.at(i); 
        for (int j = i + 1; j < len; j++) 
        {
            int second = inputs.at(j); 
            for (int k = j + 1; k < len; k++)
            {
                int third = inputs.at(k);
                if (first + second + third == desired_sum)
                {
                    std::cout << first * second * third << std::endl;
                }
            }
            
        }
    }

}