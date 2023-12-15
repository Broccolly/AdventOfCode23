#include <fstream>
#include <iostream>
#include <string>
#include <array>

int main()
{
	std::ifstream inf{ "input.txt" };

	if (!inf)
	{
		return 1;
	}

	std::string contents(std::istreambuf_iterator<char>(inf), std::istreambuf_iterator<char>());
}