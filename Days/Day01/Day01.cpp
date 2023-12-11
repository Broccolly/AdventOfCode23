#include <fstream>
#include <iostream>
#include <string>
#include <array>

#define SEARCH_WIDTH 200
#define PART2 false      // Togglefor part1 or part2

int textToNumber(std::string, bool);

int main()
{
	std::ifstream inf{ "input.txt" };

	if (!inf)
	{
		std::cerr << "Error finding input.txt";
		return 1;
	}
	int running = 0;
	char ch[SEARCH_WIDTH];
	while (inf.getline(ch, SEARCH_WIDTH))
	{
		std::string str{ ch };
		std::cout << str << std::endl;
		int num = textToNumber(str, PART2);
		std::cout << num << std::endl;

		running += num;
	}
	std::cout << running;
}

int textToNumber(std::string text, bool part2)
{
	int number{ -1 };
	std::array<std::string, 10> names{
		"zero",
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine"
	};
	int first = -1;
	int last = -1;
	for (int i{ 0 }; i < text.length(); i++)
	{
		short digit = (char)(text[i]) - '0';

		if (part2)
		{
			for (int j{ 0 }; j < names.size(); j++)
			{
				std::string name{ names[j] };
				if (text.length() < i + name.length())
				{
					continue;
				}
				std::string sub = text.substr(i, name.length());
				if (text.substr(i, (name.length())) == name)
				{
					//std::cout << sub << std::endl;

					digit = j;
					//std::cout << "Text : " << digit << std::endl;;
					// i += j - 2;
					break;
				};
			}
		}
		if (0 <= digit && digit < 10)
		{
			if (first == -1)
			{
				first = digit;
			}
			last = digit;
			continue;
		}
		//if (i >= text.length()) break;
	}
	return 10 * first + last;
}