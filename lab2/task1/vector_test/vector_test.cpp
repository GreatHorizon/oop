using namespace std;
#define CATCH_CONFIG_MAIN
#include "../vector/VectorFunctions.h"
#include "../../../catch2/catch.hpp"

TEST_CASE("Test ProcessVector()")
{
	double maxNumber = 0;

	//Обработка пустого вектора
	vector<double> numbers;
	vector<double> required;
	ProcessVector(numbers);
	CHECK(numbers == required);

	//Вектор нулей
	numbers = {0, 0, 0, 0};
	required = {0, 0, 0, 0};
	ProcessVector(numbers);
	CHECK(numbers == required);

	//Вектор положительных чисел
	numbers = { 1, 2, 3, 4};
	maxNumber = 4;
	required = {(1 / (maxNumber / 2)), (2 / (maxNumber / 2)), (3 / (maxNumber / 2)), (4 / (maxNumber / 2))};
	ProcessVector(numbers); 
	CHECK(numbers == required);

	//Вектор отрицательных чисел
	numbers = { -1, -9, -3, -14};
	maxNumber = -1;
	required = {(-1 / (maxNumber / 2)), (-9 / (maxNumber / 2)), (-3 / (maxNumber / 2)), (-14 / (maxNumber / 2))};
	ProcessVector(numbers);
	CHECK(numbers == required);

	//Дробные числа
	numbers = {-1.25, -2.33, 6.81, -9.99};
	maxNumber = 6.81;
	required = { (-1.25 / (maxNumber / 2)), (-2.33 / (maxNumber / 2)), (6.81 / (maxNumber / 2)), (-9.99 / (maxNumber / 2))};
	ProcessVector(numbers);
	CHECK(numbers == required);
}