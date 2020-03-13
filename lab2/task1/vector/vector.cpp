#include <iostream>
#include <vector>  
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iomanip>

using namespace std;

vector<double> GetVector()
{
	return vector<double>(istream_iterator<double>(cin), (istream_iterator<double>()));
}

void PrintVector(const vector<double>& numbers)
{
	cout << setprecision(3);
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, " "));
}

void ProcessVector(vector<double>& numbers)
{
	double maxElementHalf = numbers.back()/2;
	transform(numbers.begin(), numbers.end(), numbers.begin(), [&maxElementHalf](double current) {
		return (current / maxElementHalf);
	});
}

int main()
{
	vector<double> numbers = GetVector();
	sort(numbers.begin(), numbers.end());
	ProcessVector(numbers);
	PrintVector(numbers);
	return 0;
}
