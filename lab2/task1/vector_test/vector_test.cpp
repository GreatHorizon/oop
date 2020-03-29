#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../vector/VectorFunctions.h"
using namespace std;

TEST_CASE("processing empty vector should change vector")
{
	double maxNumber = 0;

	vector<double> numbers;
	vector<double> required;
	ProcessVector(numbers);
	CHECK(numbers == required);
}

TEST_CASE("should not change vector")
{
	vector<double> numbers;
	vector<double> required;
	double maxNumber = 0;

	numbers = { 0, 0, 0, 0 };
	required = { 0, 0, 0, 0 };
	ProcessVector(numbers);
	CHECK(numbers == required);
}

TEST_CASE("should divide all elements by 2")
{
	vector<double> numbers;
	vector<double> required;
	double maxNumber = 0;

	numbers = { 1, 2, 3, 4 };
	maxNumber = 4;
	required = { (1 / (maxNumber / 2)), (2 / (maxNumber / 2)), (3 / (maxNumber / 2)), (4 / (maxNumber / 2)) };
	ProcessVector(numbers);
	CHECK(numbers == required);
}

TEST_CASE("should divide all elements by -1")
{
	vector<double> numbers;
	vector<double> required;
	double maxNumber = 0;

	numbers = { -1, -9, -3, -14 };
	maxNumber = -1;
	required = { (-1 / (maxNumber / 2)), (-9 / (maxNumber / 2)), (-3 / (maxNumber / 2)), (-14 / (maxNumber / 2)) };
	ProcessVector(numbers);
	CHECK(numbers == required);
}

TEST_CASE("should divide all elements by 3")
{
	vector<double> numbers;
	vector<double> required;
	double maxNumber = 0;

	numbers = {3, 3, 3, 3};
	maxNumber = 3;
	required = { (3 / (maxNumber / 2)), (3 / (maxNumber / 2)), (3 / (maxNumber / 2)), (3 / (maxNumber / 2)) };
	ProcessVector(numbers);
	CHECK(numbers == required);

}

TEST_CASE("should divide all elements by 3.405")
{
	vector<double> numbers;
	vector<double> required;
	double maxNumber = 0;

	numbers = {-1.25, -2.33, 6.81, -9.99};
	maxNumber = 6.81;
	required = { (-1.25 / (maxNumber / 2)), (-2.33 / (maxNumber / 2)), (6.81 / (maxNumber / 2)), (-9.99 / (maxNumber / 2))};
	ProcessVector(numbers);
	CHECK(numbers == required);
}