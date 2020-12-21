#include <bits/stdc++.h>

#include <iostream>

#define LAST_TURN 2020
#define TRUE_LAST_TURN 30000000

int main()
{
    // Avoids synchro with input stream
    std::ios_base::sync_with_stdio(false);

    // Guarentees the flushing of cout before cin
    std::cin.tie(NULL);

    std::string input;
    std::unordered_map<int, int> moves;
    std::getline(std::cin, input);

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ',')
            input[i] = ' ';
    }

    std::istringstream ss(input);
    std::string word;

    int turn_number = 1;

    while (ss >> word)
    {
        moves[stol(word)] = turn_number;
        turn_number++;
    }

    int first_prev_move;
    int prev_move = 0;
    for (int t = turn_number; t < TRUE_LAST_TURN; t++)
    {
        if (t == LAST_TURN)
            first_prev_move = prev_move;

        if (moves.find(prev_move) == moves.end())
        {
            moves[prev_move] = t;
            prev_move = 0;
        }
        else
        {
            int diff = t - moves[prev_move];
            moves[prev_move] = t;
            prev_move = diff;
        }
    }

    std::cout << "Part One\n";
    std::cout << first_prev_move << "\n";

    std::cout << "Part Two\n";
    std::cout << prev_move << std::endl;
}