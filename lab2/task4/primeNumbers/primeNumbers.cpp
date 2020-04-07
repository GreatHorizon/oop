#include "stdafx.h"
#include "primeNumbers.h"

using namespace std;

vector<bool> GetSieve(int upperBound)
{
    vector<bool> sieve(upperBound + 1);
    for (int i = 2; ((i * i) < upperBound + 1); i++)
    {
        if (!sieve[i])
        {
            for (int j = (i * i); j < upperBound + 1; j += i)
            {
                if (!sieve[j])
                {
                    sieve[j] = true;
                }
            }
        }
    }

    return sieve;
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
    vector<bool> sieve = GetSieve(upperBound);
    set<int> primeNumbers;

    for (int i = 2; i < upperBound + 1; i++)
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
    cout << "\n";
}
