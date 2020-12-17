#include <bits/stdc++.h>

#include <iostream>
#include <set>
#include <map>

std::set<std::string> parent_dfs(std::map<std::string, std::set<std::string>> &parents, std::string &bag)
{
    if (parents.count(bag) == 0)
        return {};

    std::set<std::string> possible_containers = {};

    auto it = parents.find(bag);
    std::set<std::string> bags_involved = it->second;

    for (std::string parent_bag : bags_involved)
    {
        possible_containers.insert(parent_bag);
        std::set<std::string> other_containers = parent_dfs(parents, parent_bag);
        for (std::string parent_container : other_containers)
            possible_containers.insert(parent_container);
    }

    return possible_containers;
}

int children_dfs(std::map<std::string, std::set<std::pair<std::string, int>>> &children, std::string &bag)
{
    if (children.count(bag) == 0)
        return 0;

    auto it = children.find(bag);
    std::set<std::pair<std::string, int>> contained = it->second;

    int count = 0;
    for (std::pair<std::string, int> bag_tuple : contained)
        count += bag_tuple.second + bag_tuple.second * children_dfs(children, bag_tuple.first);

    return count;
}

int main()
{
    const std::regex DIGITS_ONLY("^[0-9]+$");
    std::string SHINY_GOLD = "shiny gold";

    std::string input;
    std::map<std::string, std::set<std::string>> parents = {};
    std::map<std::string, std::set<std::pair<std::string, int>>> children = {};

    int possible_parents = 0;

    while (std::getline(std::cin, input))
    {
        if (!input.empty())
        {
            std::string type;
            std::string color;
            std::string word;

            std::istringstream ss(input);

            ss >> type;
            ss >> color;
            std::string this_color = type + " " + color;
            children[this_color] = {};

            ss >> word;
            ss >> word;

            while (ss >> word)
            {
                if (std::regex_match(word, DIGITS_ONLY))
                {
                    int num_bags = stoi(word);

                    ss >> type;
                    ss >> color;
                    ss >> word;

                    std::string actual_color = type + " " + color;

                    if (parents.count(actual_color) == 0)
                        parents[actual_color] = {};

                    parents[actual_color].insert(this_color);
                    std::pair<std::string, int> tuple(actual_color, num_bags);
                    children[this_color].insert(tuple);
                }
            }
        }
    }

    std::cout << "Part One" << std::endl;
    std::cout << parent_dfs(parents, SHINY_GOLD).size() << std::endl;

    std::cout << "Part Two" << std::endl;
    std::cout << children_dfs(children, SHINY_GOLD) << std::endl;
}