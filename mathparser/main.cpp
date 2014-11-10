#include <iostream>
#include <iomanip> 
#include "includes/Parser.h"

int main()
{
	std::cout << std::setprecision(10);
	std::string input;
	
	while (std::cout << "# ", std::getline(std::cin, input))
	{
		Node *result = nullptr;

		try
		{
			Parser p(input);
			result = p.parse();
			std::cout << "-> " << result->eval() << "\n\n";
		}
		catch (const ParserException& e)
		{
			std::cout << "Invalid input: " << e.what() << "\n\n";
		}

		input.clear();

		if (result != nullptr) 
			delete result;	
	}
}