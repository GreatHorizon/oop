#include "stdafx.h"
#include "VectorFunctions.h"
using namespace std;

int main()
{
	vector<double> numbers = GetVector();
	
	ProcessVector(numbers);
	sort(numbers.begin(), numbers.end());
	PrintVector(numbers);

	return 0;
}
