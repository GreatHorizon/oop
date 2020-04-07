#pragma once

const int MAX_UPPER_BOUND = 100000000;
const int MIN_UPPER_BOUND = 2;
const int ARGUMENTS_COUNT = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintSet(const std::set<int>& primeNumbers);
std::vector<bool> GetSieve(int upperBound);
