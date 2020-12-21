#include <bits/stdc++.h>

#include <iostream>
#include <regex>

std::vector<long> bfs_addition(std::string value, int pos)
{
    if (pos == 36)
        return {(long)std::bitset<36>(value).to_ulong()};

    if (value[pos] == 'X')
    {
        std::string zero_copy = value;
        zero_copy[pos] = '0';
        std::vector<long> zero_copies = bfs_addition(zero_copy, pos + 1);

        std::string one_copy = value;
        one_copy[pos] = '1';
        std::vector<long> one_copies = bfs_addition(one_copy, pos + 1);

        zero_copies.insert(zero_copies.end(), one_copies.begin(), one_copies.end());
        return zero_copies;
    }
    else
        return bfs_addition(value, pos + 1);
}

int main()
{
    // Avoids synchro with input stream
    std::ios_base::sync_with_stdio(false);

    // Guarentees the flushing of cout before cin
    std::cin.tie(NULL);

    std::string input;

    std::regex BRACKETS_CONTENT("^mem:?\\[(.*)\\]");
    std::string bitmask;
    std::map<long, std::bitset<36>> addresses;
    std::map<long, std::bitset<36>> true_addresses;

    while (std::getline(std::cin, input))
    {
        if (!input.empty())
        {
            std::string word;
            std::istringstream ss(input);

            ss >> word;

            if (word == "mask")
            {
                ss >> word;
                ss >> word;
                bitmask = word;
            }
            else
            {
                std::smatch match;

                std::regex_match(word, match, BRACKETS_CONTENT);
                int addr = stoi(match[1]);

                ss >> word;
                ss >> word;

                long val = stol(word);

                std::string value = std::bitset<36>(val).to_string();
                std::string floating_value = std::bitset<36>(addr).to_string();

                for (int i = 0; i < 36; i++)
                {
                    if (bitmask[i] == 'X')
                        floating_value[i] = 'X';
                    else if (bitmask[i] == '1')
                    {
                        floating_value[i] = '1';
                    }

                    if (bitmask[i] != 'X')
                        value[i] = bitmask[i];
                }

                addresses[addr] = std::bitset<36>(value);

                std::vector<long> addresses_to_overwrite = bfs_addition(floating_value, 0);
                for (auto new_addr : addresses_to_overwrite)
                    true_addresses[new_addr] = std::bitset<36>(val);
            }
        }
    }

    long total_sums = 0;
    long true_sums = 0;

    for (auto tuple : addresses)
        total_sums += tuple.second.to_ulong();

    for (auto tuple : true_addresses)
        true_sums += tuple.second.to_ulong();

    std::cout << "Part One\n";
    std::cout << total_sums << "\n";

    std::cout << "Part Two\n";
    std::cout << true_sums << std::endl;
}