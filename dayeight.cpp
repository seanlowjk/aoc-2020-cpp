#include <bits/stdc++.h>

#include <iostream>
#include <vector>

int main()
{
    std::string input;

    std::vector<std::pair<std::string, int>> instructions(0);
    std::vector<bool> visited(0);

    while (std::getline(std::cin, input))
    {
        if (!input.empty())
        {
            std::istringstream ss(input);
            std::string operation;
            std::string number;

            ss >> operation;
            ss >> number;

            int num = stoi(number.substr(1, number.length()));

            if (number.at(0) == '-')
                num *= -1;

            std::pair<std::string, int> instruction(operation, num);
            instructions.push_back(instruction);
            visited.push_back(false);
        }
    }

    const int total_instructions = instructions.size();

    int new_acc = 0;

    for (int i = 0; i < total_instructions; i++)
    {
        if (instructions.at(i).first == "acc")
            continue;

        std::vector<std::pair<std::string, int>> new_instructions(instructions);
        std::vector<bool> new_visited(visited);
        if (new_instructions.at(i).first == "nop")
            new_instructions[i].first = "jmp";
        else
            new_instructions[i].first = "nop";

        int new_instruction_index = 0;
        while (true)
        {
            if (new_visited.at(new_instruction_index))
            {
                new_acc = 0;
                break;
            }

            new_visited[new_instruction_index] = true;
            std::pair<std::string, int> instruction = new_instructions.at(new_instruction_index);

            if (instruction.first == "acc")
            {
                new_acc += instruction.second;
                new_instruction_index++;
            }
            else if (instruction.first == "jmp")
                new_instruction_index += instruction.second;
            else
                new_instruction_index++;

            if (new_instruction_index == total_instructions)
            {
                i = total_instructions;
                break;
            }

            new_instruction_index %= total_instructions;
        }
    }

    int instruction_index = 0;
    int total_acc = 0;
    while (true)
    {
        if (visited.at(instruction_index))
            break;

        visited[instruction_index] = true;
        std::pair<std::string, int> instruction = instructions.at(instruction_index);

        if (instruction.first == "acc")
        {
            total_acc += instruction.second;
            instruction_index++;
        }
        else if (instruction.first == "jmp")
            instruction_index += instruction.second;
        else
            instruction_index++;

        instruction_index %= total_instructions;
    }

    std::cout << "Part One" << std::endl;
    std::cout << total_acc << std::endl;

    std::cout << "Part Two" << std::endl;
    std::cout << new_acc << std::endl;
}