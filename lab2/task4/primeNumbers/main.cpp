#include "stdafx.h"
#include "primeNumbers.h"

using namespace std;

optional<int> GetArgument(int argc, char* argv[])
{
    if (argc < ARGUMENTS_COUNT)
    {
        cout << "Invalid argument count" << endl;
        cout << "Usage <upperBound>";
        return nullopt;
    }

    int upperBound = 0;
    if (!CheckArgument(argv[1], upperBound))
    {
        cout << "upperBound should be a number from 0 to 100000000" << endl;
        return nullopt;
    }

    return upperBound;
}

int main(int argc, char* argv[])
{
    auto arg = GetArgument(argc, argv);

    if (!arg)
    {
        return 1;
    }

    set<int> primeNumbers = GeneratePrimeNumbersSet(arg.value());
    PrintSet(primeNumbers);

    return 0;
}
