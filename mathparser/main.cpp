#include <iostream>
#include <iomanip> 
#include "includes/Parser.h"

void process_command_line(const std::string& input)
{
	if (input == "/help")
	{
		std::cout
			<< "\n"
			<< "  sin(x)    - calculates the sinus of x  \n"
			<< "  cos(x)    - calculates the cosinus of x\n"
			<< "  tan(x)    - calculates the tangens of x\n"
			<< "  log(x)    - calculates the natural logarithm of x\n\n"
			<< "  sqrt(x)   - calculates the square root of x\n"
			<< "  pow(x, y) - calculates x high y\n\n"
			<< "  digsum(x) - calculates the digit sum of x\n"
			<< "  ceil(x)   - rounds x upward\n"
			<< "  floor(x)  - rounds x downward\n\n"
			<< "  e         - eularian number\n"
			<< "  pi        - circular number pi\n"
			<< "\n";
	}

	if (input == "/clear")
	{
		#ifdef _WIN32
			system("cls");
		#else
			system("clear");
		#endif
	}

	if (input == "/maxval")
	{
		std::cout << "-> " << std::numeric_limits<number>::max() << "\n\n";
	}
}

int main()
{
	std::cout << std::setprecision(10);
	std::string input;
	
	while (std::cout << "# ", std::getline(std::cin, input))
	{
		process_command_line(input);

		try
		{
			Parser p(input);
			auto result = p.parse();
			std::cout << "-> " << result->eval() << "\n\n";
		}
		catch (const ParserException& e)
		{
			std::cout << "Invalid input: " << e.what() << "\n\n";
		}

		input.clear();
	}
}