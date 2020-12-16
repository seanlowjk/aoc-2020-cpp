#include <iostream>
#include <set>

int main()
{
    std::string input;
    int total_answered = 0;
    int all_answered = 0;

    std::set<char> questions = {};

    bool has_started_tracking = false;
    std::set<char> all_questions = {};

    while (std::getline(std::cin, input))
    {
        if (input.empty())
        {
            total_answered += questions.size();
            questions.clear();

            all_answered += all_questions.size();
            has_started_tracking = false;
            all_questions.clear();
        }
        else
        {
            if (!has_started_tracking)
            {
                has_started_tracking = true;
                for (int i = 0; i < input.length(); i++)
                    all_questions.insert(input.at(i));
            }
            else
            {
                std::set<char> temp = {};
                for (int i = 0; i < input.length(); i++)
                {
                    if (all_questions.count(input.at(i)) > 0)
                        temp.insert(input.at(i));
                }

                all_questions = temp;
            }

            for (int i = 0; i < input.length(); i++)
                questions.insert(input.at(i));
        }
    }

    total_answered += questions.size();
    all_answered += all_questions.size();

    std::cout << "Part One" << std::endl;
    std::cout << total_answered << std::endl;

    std::cout << "Part Two" << std::endl;
    std::cout << all_answered << std::endl;
}