#include "stdafx.h"
#include "primeNumbers.h"

using namespace std;

optional<int> CheckArgument(const string& argument)
{
    int upperBound;
    size_t* errorPosition = new size_t;

    try
    {
        upperBound = stoi(argument, errorPosition, 10);
    }
    catch (exception)
    {
        return nullopt;
    }

    if (argument[*errorPosition] != '\0')
    {
        return nullopt;
    }
    else if (upperBound < MIN_UPPER_BOUND || upperBound > MAX_UPPER_BOUND)
    {
        return  nullopt;
    }

    return upperBound;
}

optional<int> GetArgument(int argc, char* argv[])
{
    if (argc < ARGUMENTS_COUNT)
    {
        cout << "Invalid argument count" << "\n";
        cout << "Usage <upperBound>";   
        return nullopt;
    }

    optional arg = CheckArgument(argv[1]);

    if (!arg)
    {
        cout << "upperBound should be a number from "<< MIN_UPPER_BOUND << " to "<< MAX_UPPER_BOUND << "\n";
        return nullopt;
    }

    return arg;
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
