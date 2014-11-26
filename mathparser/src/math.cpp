#include "../includes/math.h"

math::number math::digitsum(number number)
{
	int result = 0;

	while (number > 0)
	{
		result += static_cast<long long>(number) % 10;
		number /= 10;
	}

	return result;
}