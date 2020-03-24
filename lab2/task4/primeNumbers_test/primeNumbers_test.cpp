#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "..\\primeNumbers\primeNumbers.h"

using namespace std;

TEST_CASE("test GeneratePrimeNumbersSet()")
{
	int upperBound = 10;
	set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	set<int> requiredNumbersSet = {2,3,5,7};
	REQUIRE(primeNumbersSet == requiredNumbersSet);

	upperBound = 30;
	primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	requiredNumbersSet = {2 ,3, 5, 7, 11, 13, 17, 19, 23, 29};
	REQUIRE(primeNumbersSet == requiredNumbersSet);

	upperBound = 100;
	primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	requiredNumbersSet = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 
		41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	REQUIRE(primeNumbersSet == requiredNumbersSet);

	//Минимальная верхняя граница
	upperBound = 2;
	primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	requiredNumbersSet = {2};
	REQUIRE(primeNumbersSet == requiredNumbersSet);

	//Максимальная верхняя граница
	int setSize;
	upperBound = 100000000;
	primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	setSize = primeNumbersSet.size();
	REQUIRE(setSize == 5761455);
}
