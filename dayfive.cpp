#include <iostream>

int main()
{
    const int START_ROW = 0;
    const int END_ROW = 6;
    const int START_COL = 7;
    const int END_COL = 9;
    const int FRONT_SEAT = 0;
    const int BACK_SEAT = 127;
    const int LEFT_SEAT = 0;
    const int RIGHT_SEAT = 7;
    const int TOTAL_SEATS = (BACK_SEAT - FRONT_SEAT + 1) * (RIGHT_SEAT - LEFT_SEAT + 1);

    int max_seat = -1;
    int seat = 0;

    bool visited[TOTAL_SEATS];

    for (int i = 0; i < TOTAL_SEATS; i++)
        visited[i] = false;

    std::string input;
    while (std::getline(std::cin, input))
    {
        int start_row = FRONT_SEAT;
        int end_row = BACK_SEAT;

        int start_col = LEFT_SEAT;
        int end_col = RIGHT_SEAT;
        for (int i = START_ROW; i < END_ROW; i++)
        {
            if (input.at(i) == 'F')
                end_row = (start_row + end_row - 1) / 2;
            else
                start_row = (start_row + end_row + 1) / 2;
        }

        if (input.at(END_ROW) == 'F')
            seat = 8 * start_row;
        else
            seat = 8 * end_row;

        for (int i = START_COL; i < END_COL; i++)
        {
            if (input.at(i) == 'L')
                end_col = (start_col + end_col - 1) / 2;
            else
                start_col = (start_col + end_col + 1) / 2;
        }

        if (input.at(END_COL) == 'L')
            seat += start_col;
        else
            seat += end_col;

        visited[seat] = true;
        max_seat = std::max(max_seat, seat);
    }

    int my_seat;
    for (int i = 1; i < TOTAL_SEATS - 1; i++)
    {
        if (!visited[i] && visited[i - 1] && visited[i + 1])
            my_seat = i;
    }

    std::cout << "Part One" << std::endl;
    std::cout << max_seat << std::endl;

    std::cout << "Part Two" << std::endl;
    std::cout << my_seat << std::endl;
}