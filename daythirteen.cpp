#include <bits/stdc++.h>

#include <iostream>
#include <vector>

int main()
{
    // Avoids synchro with input stream
    std::ios_base::sync_with_stdio(false);

    // Guarentees the flushing of cout before cin
    std::cin.tie(NULL);

    std::string num;
    std::string buses;

    long long product = 1;
    long earliest_departure;
    std::vector<long> bus_numbers;

    std::getline(std::cin, num);
    std::getline(std::cin, buses);

    earliest_departure = stol(num);
    for (int i = 0; i < buses.length(); i++)
    {
        if (buses[i] == ',')
            buses[i] = ' ';
    }

    std::istringstream ss(buses);

    std::string input;
    while (ss >> input)
    {
        if (input != "x")
        {
            bus_numbers.push_back(stol(input));
            product *= stol(input);
        }
        else
        {
            bus_numbers.push_back(0);
        }
    }

    long bus_num;
    long min_waiting_time = LONG_MAX;

    for (int i = 0; i < bus_numbers.size(); i++)
    {
        if (bus_numbers[i] == 0)
            continue;

        long times = earliest_departure / bus_numbers[i];

        long prev_time = times * bus_numbers[i];
        long next_time = (times + 1) * bus_numbers[i];

        long waiting_time = next_time - earliest_departure;
        if (waiting_time < min_waiting_time)
        {
            min_waiting_time = waiting_time;
            bus_num = bus_numbers[i];
        }
    }

    long part_one = min_waiting_time * bus_num;
    long earliest = 0;

    for (int i = 0; i < bus_numbers.size(); i++)
    {
        long busNo = bus_numbers[i];
        if (busNo == 0)
            continue;

        long remainder = i;
        long rest = product / busNo;
        long result = ((busNo - (i % busNo)) % busNo);
        int j = 0;
        while (true)
        {
            if ((rest * j) % busNo == result)
                break;

            j += 1;
        }

        earliest = (earliest + (rest * j)) % product;
    }

    std::cout << "Part One\n";
    std::cout << part_one << "\n";

    std::cout << "Part Two\n";
    std::cout << earliest << std::endl;
}