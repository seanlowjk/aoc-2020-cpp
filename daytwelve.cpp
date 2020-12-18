#include <bits/stdc++.h>

#include <iostream>
#include <vector>

#define NUM_DIRECTIONS 4
#define RIGHT_ANGLE 90

int main()
{
    // Avoids synchro with input stream
    std::ios_base::sync_with_stdio(false);

    // Guarentees the flushing of cout before cin
    std::cin.tie(NULL);

    std::string input;
    std::vector<std::string> instructions;

    // N, E, S, W
    int x_directions[4] = {0, 1, 0, -1};
    int y_directions[4] = {1, 0, -1, 0};

    long x_pos = 0;
    long y_pos = 0;
    int curr_direction = 1;

    while (std::getline(std::cin, input))
    {
        if (!input.empty())
            instructions.push_back(input);
    }

    for (int i = 0; i < instructions.size(); i++)
    {
        std::string instruction = instructions[i];

        char command = instruction[0];
        long move = stol(instruction.substr(1, instruction.length()));

        if (command == 'N')
            y_pos += move;
        else if (command == 'S')
            y_pos -= move;
        else if (command == 'E')
            x_pos += move;
        else if (command == 'W')
            x_pos -= move;
        else if (command == 'L')
            curr_direction -= move / RIGHT_ANGLE;
        else if (command == 'R')
            curr_direction += move / RIGHT_ANGLE;
        else
        {
            x_pos += (x_directions[curr_direction] * move);
            y_pos += (y_directions[curr_direction] * move);
        }

        if (curr_direction < 0)
            curr_direction += NUM_DIRECTIONS;

        curr_direction %= NUM_DIRECTIONS;
    }

    long manhattan_distance = std::abs(x_pos) + std::abs(y_pos);

    x_pos = 0;
    y_pos = 0;

    int x_waypoint = 10;
    int y_waypoint = 1;

    for (int i = 0; i < instructions.size(); i++)
    {
        std::string instruction = instructions[i];

        char command = instruction[0];
        long move = stol(instruction.substr(1, instruction.length()));

        if (command == 'N')
            y_waypoint += move;
        else if (command == 'S')
            y_waypoint -= move;
        else if (command == 'E')
            x_waypoint += move;
        else if (command == 'W')
            x_waypoint -= move;
        else if (command == 'L')
        {
            int rotations = (move / RIGHT_ANGLE);
            for (int i = 0; i < rotations; i++)
            {
                int temp = x_waypoint;
                x_waypoint = -1 * y_waypoint;
                y_waypoint = temp;
            }
        }
        else if (command == 'R')
        {
            int rotations = (move / RIGHT_ANGLE);
            for (int i = 0; i < rotations; i++)
            {
                int temp = -1 * x_waypoint;
                x_waypoint = y_waypoint;
                y_waypoint = temp;
            }
        }
        else
        {
            x_pos += (move * x_waypoint);
            y_pos += (move * y_waypoint);
        }

        if (curr_direction < 0)
            curr_direction += NUM_DIRECTIONS;

        curr_direction %= NUM_DIRECTIONS;
    }

    long new_manhattan_distance = std::abs(x_pos) + std::abs(y_pos);

    std::cout << "Part One\n";
    std::cout << manhattan_distance << "\n";

    std::cout << "Part Two\n";
    std::cout << new_manhattan_distance << std::endl;
}