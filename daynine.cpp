#include <bits/stdc++.h>

#include <iostream>
#include <deque>

#define MAX_NUMBERS_BEFORE 25

int main()
{
    // Avoids synchro with input stream
    std::ios_base::sync_with_stdio(false);

    // Guarentees the flushing of cout before cin
    std::cin.tie(NULL);

    std::string input;
    std::deque<long> previous;
    std::vector<long> sums;
    std::vector<long> nums;

    long bug = 0;
    long keys = 0;
    int count = 0;

    while (std::getline(std::cin, input))
    {
        if (!input.empty())
        {
            count += 1;

            long num = stol(input);
            nums.push_back(num);

            if (sums.size() == 0)
                sums.push_back(num);
            else
                sums.push_back(num + sums[count - 2]);

            if (previous.size() < MAX_NUMBERS_BEFORE)
                previous.push_back(num);
            else
            {
                bool has_pair = false;
                for (int i = 0; i < MAX_NUMBERS_BEFORE; i++)
                {
                    for (int j = i + 1; j < MAX_NUMBERS_BEFORE; j++)
                    {
                        if (previous[i] + previous[j] == num)
                            has_pair = true;
                    }
                }

                if (!has_pair)
                {
                    bug = num;
                    break;
                }
                else
                {
                    previous.pop_front();
                    previous.push_back(num);
                }
            }
        }
    }

    bool has_found = false;
    for (int i = 0; i < count; i++)
    {
        if (has_found)
            break;

        for (int j = i + 1; j < count; j++)
        {
            if (sums[j] - sums[i] == bug)
            {
                long min = nums[i + 1];
                long max = nums[i + 1];

                for (int k = i + 2; k <= j; k++)
                {
                    min = std::min(min, nums[k]);
                    max = std::max(max, nums[k]);
                }

                keys = min + max;
                has_found = true;
                break;
            }
        }
    }

    std::cout << "Part One\n";
    std::cout << bug << "\n";

    std::cout << "Part Two\n";
    std::cout << keys << std::endl;
}