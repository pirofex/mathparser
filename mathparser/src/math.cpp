#include "../includes/math.h"

<<<<<<< HEAD
math::number math::digitsum(number number)
=======
math::number math::digitsum(math::number number)
>>>>>>> origin/master
{
	math::number result = 0;

	while (number > 0)
	{
		result += static_cast<long long>(number) % 10;
		number /= 10;
	}

	return result;
}