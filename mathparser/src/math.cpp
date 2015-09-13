#include "../includes/math.h"

namespace math {

number digitsum(number value)
{
	number result = 0;

	while (value)
	{
		result += static_cast<long long>(value) % 10;
		value /= 10;
	}

	return result;
}

} // namespace math