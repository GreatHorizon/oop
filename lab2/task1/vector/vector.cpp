#include "VectorFunctions.h"

int main()
{
	vector<double> numbers = GetVector();
	

	if (!ProcessVector(numbers))
	{
		return 1;
	}
	sort(numbers.begin(), numbers.end());
	PrintVector(numbers);

	return 0;
}
