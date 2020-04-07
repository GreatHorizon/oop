#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "..\\primeNumbers\primeNumbers.h"

using namespace std;

TEST_CASE("upperBound = 0 GeneratePrimeNumbersSet() should return {}")
{
	set<int> primeNumbersSet = GeneratePrimeNumbersSet(0);
	set<int> requiredNumbersSet = {};
	REQUIRE(primeNumbersSet == requiredNumbersSet);
}

TEST_CASE("upperBound = 1 GeneratePrimeNumbersSet() should return {}")
{
	set<int> primeNumbersSet = GeneratePrimeNumbersSet(1);
	set<int> requiredNumbersSet = {};
	REQUIRE(primeNumbersSet == requiredNumbersSet);
}

TEST_CASE("upperBound = 2 GeneratePrimeNumbersSet() should return {2}")
{
	set<int> primeNumbersSet = GeneratePrimeNumbersSet(2);
	set<int> requiredNumbersSet = {2};
	REQUIRE(primeNumbersSet == requiredNumbersSet);
}

TEST_CASE("upperBound = 10 GeneratePrimeNumbersSet() should return {2, 3, 5, 7}")
{
	set<int> primeNumbersSet = GeneratePrimeNumbersSet(10);
	set<int> requiredNumbersSet = {2, 3, 5, 7};
	REQUIRE(primeNumbersSet == requiredNumbersSet);
}

TEST_CASE("upperBound = 30 GeneratePrimeNumbersSet() should return {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}")
{
	set<int> primeNumbersSet = GeneratePrimeNumbersSet(30);
	set<int> requiredNumbersSet = { 2 ,3, 5, 7, 11, 13, 17, 19, 23, 29 };
	REQUIRE(primeNumbersSet == requiredNumbersSet);
}

#if NDEBUG	
TEST_CASE("upperbound = 100000000 GeneratePrimeNumbersSet() should return set with size 5761455")
{
	set<int> primeNumbersSet = GeneratePrimeNumbersSet(100000000);
	int setSize = primeNumbersSet.size();
	CHECK(setSize == 5761455);
}
#endif