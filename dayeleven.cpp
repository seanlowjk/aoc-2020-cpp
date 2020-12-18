#include <bits/stdc++.h>

#include <iostream>
#include <algorithm>
#include <vector>

#define NUM_DIRECTIONS 8

#define SOFT_TOLERANCE 4
#define HARD_TOLERANCE 5

int main()
{
    // Avoids synchro with input stream
    std::ios_base::sync_with_stdio(false);

    // Guarentees the flushing of cout before cin
    std::cin.tie(NULL);

    int y_directions[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int x_directions[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    std::string input;
    std::vector<std::string> rows;

    while (std::getline(std::cin, input))
    {
        if (!input.empty())
            rows.push_back(input);
    }

    std::vector<std::string> prev_rows(rows);
    std::vector<std::string> next_rows(rows);

    int num_rows = rows.size();
    int num_cols = rows[0].length();
    int total_occupied = 0;

    while (true)
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                int count = 0;
                for (int k = 0; k < NUM_DIRECTIONS; k++)
                {
                    int next_y = i + y_directions[k];
                    int next_x = j + x_directions[k];

                    if (next_y >= 0 && next_y < num_rows && next_x >= 0 && next_x < num_cols)
                    {
                        if (prev_rows[next_y][next_x] == '#')
                            count++;
                    }
                }

                if (count == 0 && next_rows[i][j] == 'L')
                    next_rows[i][j] = '#';
            }
        }

        prev_rows = next_rows;

        total_occupied = 0;
        bool has_no_changes = true;

        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                int count = 0;
                for (int k = 0; k < NUM_DIRECTIONS; k++)
                {
                    int next_y = i + y_directions[k];
                    int next_x = j + x_directions[k];

                    if (next_y >= 0 && next_y < num_rows && next_x >= 0 && next_x < num_cols)
                    {
                        if (prev_rows[next_y][next_x] == '#')
                            count++;
                    }
                }

                if (count >= SOFT_TOLERANCE && next_rows[i][j] == '#')
                {
                    next_rows[i][j] = 'L';
                    has_no_changes = false;
                }
                else if (next_rows[i][j] == '#')
                    total_occupied++;
            }
        }

        if (has_no_changes)
            break;

        prev_rows = next_rows;
    }

    prev_rows = rows;
    next_rows = rows;
    int newly_occupied = 0;

    while (true)
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                int count = 0;
                for (int k = 0; k < NUM_DIRECTIONS; k++)
                {
                    int next_y = i + y_directions[k];
                    int next_x = j + x_directions[k];

                    while (true)
                    {
                        if (next_y >= 0 && next_y < num_rows && next_x >= 0 && next_x < num_cols)
                        {

                            if (prev_rows[next_y][next_x] == '#')
                            {
                                count++;
                                break;
                            }
                            else if (prev_rows[next_y][next_x] == '.')
                            {
                                next_y += y_directions[k];
                                next_x += x_directions[k];
                                continue;
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                if (count == 0 && next_rows[i][j] == 'L')
                    next_rows[i][j] = '#';
            }
        }

        prev_rows = next_rows;

        newly_occupied = 0;
        bool has_no_changes = true;

        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                int count = 0;
                for (int k = 0; k < NUM_DIRECTIONS; k++)
                {
                    int next_y = i + y_directions[k];
                    int next_x = j + x_directions[k];

                    while (true)
                    {
                        if (next_y >= 0 && next_y < num_rows && next_x >= 0 && next_x < num_cols)
                        {
                            if (prev_rows[next_y][next_x] == '#')
                            {
                                count++;
                                break;
                            }
                            else if (prev_rows[next_y][next_x] == '.')
                            {
                                next_y += y_directions[k];
                                next_x += x_directions[k];
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                if (count >= HARD_TOLERANCE && next_rows[i][j] == '#')
                {
                    next_rows[i][j] = 'L';
                    has_no_changes = false;
                }
                else if (next_rows[i][j] == '#')
                    newly_occupied++;
            }
        }

        if (has_no_changes)
            break;

        prev_rows = next_rows;
    }

    std::cout << "Part One\n";
    std::cout << total_occupied << "\n";

    std::cout << "Part Two\n";
    std::cout << newly_occupied << std::endl;
}