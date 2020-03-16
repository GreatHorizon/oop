#include "stdafx.h"
vector<double> GetVector()
{
	return vector<double>(istream_iterator<double>(cin), (istream_iterator<double>()));
}

void PrintVector(const vector<double>& numbers)
{
	cout << setprecision(3);
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, " "));
	cout << endl;
}

bool ProcessVector(std::vector<double>& numbers)
{
	if (!numbers.empty())
	{
		double maxElementHalf = *max_element(numbers.begin(), numbers.end()) / 2;
		if (maxElementHalf)
		{
			transform(numbers.begin(), numbers.end(), numbers.begin(), [&maxElementHalf](double current)
			{
				return (current / maxElementHalf);
			});
		}
		return true;	
	}
	else
	{
		cout << "Vector should contain numbers";
		return false;
	}
}