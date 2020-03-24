#include "stdafx.h"
#include "primeNumbers.h"

using namespace std;

bool CheckArgument(string argument, int upperBound)
{   
    size_t* errorPosition = new size_t;
    try
    {
        upperBound = stoi(argument, errorPosition, 10);
    }
    catch (exception)
    {
        return false;
    }

    if (argument[*errorPosition] != '\0')
    {
        return false;
    }
    else if (upperBound < MIN_UPPER_BOUND || upperBound > MAX_UPPER_BOUND)
    {
        return  false;
    }

    return true;
}

vector<bool> GetSieve(int upperBound)
{
    vector<bool> numbersVector(upperBound);
    for (int i = 2; ((i * i) < upperBound + 1); i++)
    {
        if (!numbersVector[i])
        {
            for (int j = (i * i); j < upperBound + 1; j += i)
            {
                if (!numbersVector[j])
                {
                    numbersVector[j] = true;
                }
            }

        }
    }

    return numbersVector;
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
    vector<bool> sieve = GetSieve(upperBound);
    set<int> primeNumbers;

    for (int i = 2; i <= upperBound; i++)
    {
        if (!sieve[i])
        {
            primeNumbers.insert(i);
        }
    }

    return primeNumbers;
}

void PrintSet(const set<int>& primeNumbers)
{
    copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}
