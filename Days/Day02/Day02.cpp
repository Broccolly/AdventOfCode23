#include <iostream>
#include <fstream>
#include <string>

#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14
#define PART2 true

std::string nextWord(std::string&);



enum Mode {
	START,
	ID,
	VALUE,
	COLOUR,
	END
};

int main()
{
	std::ifstream inf{ "input.txt" };
	if (!inf)
	{
		std::cerr << "Could not find file!";
		return 1;
	}

	int total = 0;

	while (inf)
	{
		Mode mode = START;
		std::string strInput;
		std::getline(inf, strInput);
		std::cout << strInput << std::endl;
		
		std::string word;

		int id = 0;
		int toAdd = 0;
		int count[3]{ 0,0,0 };
		int max[3]{ 0,0,0 };

		bool reset = false;

		while ((word = nextWord(strInput)) != "")
		{
			if (mode == START)
			{
				mode = ID;
			}
			else if (mode == ID)
			{
				word = word.substr(0, word.length() - 1);
				id = std::stoi(word, nullptr, 10);
				std::cout << id << std::endl;
				if (!PART2) total += id;
				mode = VALUE;
			}
			else if (mode == VALUE)
			{
				toAdd = std::stoi(word, nullptr, 10);
				mode = COLOUR;
			}
			else if (mode == COLOUR)
			{
				if (word[word.length() - 1] == ';')
				{
					reset = true;
					word.erase(word.length() - 1, 1);
				}
				else if (word[word.length() - 1] == ',')
				{
					word.erase(word.length() - 1, 1);
				}
				else
				{
					reset = true; //EOL
				}

				///////////////////
				if (word == "red")
				{
					count[0] += toAdd;
				}
				if (word == "green")
				{
					count[1] += toAdd;
				}
				if (word == "blue")
				{
					count[2] += toAdd;
				}
				mode = VALUE;
			}
			if (reset)
			{
				std::cout << count[0] << ' ' << count[1] << ' ' << count[2] << std::endl;
				if (PART2)
				{
					for (int i{ 0 }; i < 3; i++)
					{
						if (count[i] > max[i])
						{
							max[i] = count[i];
						}
					}
				}
				else
				{
					if (count[0] > RED_MAX || count[1] > GREEN_MAX || count[2] > BLUE_MAX)
					{
						std::cout << "NOT POSSIBLE" << std::endl;
						total -= id;
						break;  // Don't want to double count
					}
				}
				count[0] = 0;
				count[1] = 0;
				count[2] = 0;
				reset = false;
			}
		}
		if (PART2) total += max[0] * max[1] * max[2];
	}
	std::cout << "Total : " << total;
}

std::string nextWord(std::string& string)
{
	std::string out{ "" };

	while (string.length() > 0 && string[0] != ' ')
	{
		out.append(string.substr(0,1));
		string.erase(0, 1);
	}
	if (string.length() > 0 && string[0] == ' ')
	{
		string.erase(0, 1);
	}
	return out;
}