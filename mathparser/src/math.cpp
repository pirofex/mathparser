#include "../includes/math.h"

math::number math::digitsum(int number)
{
	int result = 0;

	while (number > 0)
	{
		result += number % 10;
		number /= 10;
	}

	return result;
}