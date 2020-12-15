#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <set>

std::pair<std::vector<std::string>, std::vector<std::string>> get_headers(char *&input)
{
    const std::regex DIGITS_ONLY("^[0-9]+$");
    const std::regex HEIGHT_ONLY("(^[0-9]+)(cm|in)");
    const std::regex HAIR_COLOR_ONLY("#([0-9]|[a-f])+");
    const std::regex EYE_COLOR_ONLY("amb|blu|brn|gry|grn|hzl|oth");

    std::set<std::string> all_headers = {"hcl", "iyr", "eyr", "ecl", "pid", "byr", "hgt", "cid"};
    std::vector<std::string> headers(0);
    std::vector<std::string> verified_headers(0);

    std::istringstream ss(input);
    std::string header;
    std::string value;

    while (ss >> header)
    {
        ss >> value;

        bool is_header = all_headers.find(header) != all_headers.end();
        bool is_right_header = false;

        if (header == "byr")
        {
            if (std::regex_match(value, DIGITS_ONLY) && stoi(value) >= 1920 && stoi(value) <= 2002)
                is_right_header = true;
        }

        if (header == "iyr")
        {
            if (std::regex_match(value, DIGITS_ONLY) && stoi(value) >= 2010 && stoi(value) <= 2020)
                is_right_header = true;
        }

        if (header == "eyr")
        {
            if (std::regex_match(value, DIGITS_ONLY) && stoi(value) >= 2020 && stoi(value) <= 2030)
                is_right_header = true;
        }

        if (header == "hgt")
        {
            std::smatch match;
            if (std::regex_match(value, match, HEIGHT_ONLY))
            {
                if (match[2] == "cm")
                    is_right_header = stoi(match[1]) >= 150 && stoi(match[1]) <= 193;
                else
                    is_right_header = stoi(match[1]) >= 59 && stoi(match[1]) <= 76;
            }
        }

        if (header == "hcl" && std::regex_match(value, HAIR_COLOR_ONLY) && value.length() == 7)
            is_right_header = true;

        if (header == "ecl" && std::regex_match(value, EYE_COLOR_ONLY))
            is_right_header = true;

        if (header == "pid" && std::regex_match(value, DIGITS_ONLY) && value.length() == 9)
            is_right_header = true;

        if (is_header)
            headers.push_back(header);

        if (is_right_header)
            verified_headers.push_back(header);
    }

    return std::make_pair(headers, verified_headers);
}

int main()
{
    std::set<std::string> headers = {};
    std::set<std::string> verified_headers = {};
    std::set<std::string> all_headers = {"hcl", "iyr", "eyr", "ecl", "pid", "byr", "hgt", "cid"};
    std::set<std::string> valid_headers = {"hcl", "iyr", "eyr", "ecl", "pid", "byr", "hgt"};

    std::string input;

    int valid_passports = 0;
    int accurate_passports = 0;

    while (std::getline(std::cin, input))
    {
        if (input.empty())
        {
            if (headers == all_headers || (headers == valid_headers))
                valid_passports++;

            if (verified_headers == all_headers || (verified_headers == valid_headers))
                accurate_passports++;

            headers.clear();
            verified_headers.clear();
        }
        else
        {
            for (int i = 0; i < input.length(); i++)
            {
                if (input[i] == ':')
                {
                    input[i] = ' ';
                }
            }
            char *io_input = &input[0];

            std::pair<std::vector<std::string>, std::vector<std::string>> compiled_headers = get_headers(io_input);

            for (std::string &s : compiled_headers.first)
                headers.insert(s);

            for (std::string &s : compiled_headers.second)
                verified_headers.insert(s);
        }
    }

    if (headers == all_headers || (headers == valid_headers))
        valid_passports++;

    if (verified_headers == all_headers || (verified_headers == valid_headers))
        accurate_passports++;

    std::cout << "Part One" << std::endl;
    std::cout << valid_passports << std::endl;

    std::cout << "Part Two" << std::endl;
    std::cout << accurate_passports << std::endl;
}