#include <bits/stdc++.h>

#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    // Avoids synchro with input stream
    std::ios_base::sync_with_stdio(false);

    // Guarentees the flushing of cout before cin
    std::cin.tie(NULL);

    std::string input;
    std::vector<long> voltages;

    while (std::getline(std::cin, input))
    {
        if (!input.empty())
            voltages.push_back(stol(input));
    }

    std::sort(voltages.begin(), voltages.end(), [](int i, int j) { return i < j; });

    long one_differences = 0;
    long three_differences = 1;

    if (voltages[0] == 1)
        one_differences++;
    else if (voltages[0] == 3)
        three_differences++;

    for (int i = 0; i < voltages.size() - 1; i++)
    {
        if (voltages[i + 1] - voltages[i] == 1)
            one_differences++;
        else
            three_differences++;
    }

    long multi_differences = one_differences * three_differences;

    long dp[voltages.back() + 1];
    for (int i = 0; i <= voltages.back(); i++)
        dp[i] = 0;

    dp[0] = 1;

    for (int i = 0; i < voltages.size(); i++)
    {
        int voltage_value = voltages[i];

        if (voltage_value == 1)
            dp[1] = 1;
        else if (voltage_value == 2)
            dp[2] = 2;
        else
            dp[voltage_value] = dp[voltage_value - 1] + dp[voltage_value - 2] + dp[voltage_value - 3];
    }

    long long num_ways = dp[voltages.back()];

    std::cout << "Part One\n";
    std::cout << multi_differences << "\n";

    std::cout << "Part Two\n";
    std::cout << num_ways << std::endl;
}