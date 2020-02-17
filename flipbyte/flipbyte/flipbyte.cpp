﻿#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "flipbyte.h"
#include <fstream>
#include <string>
using namespace std;

const int UPPER_LIMIT = 255;
const int LOWER_LIMIT = 0;

enum Errors
{
    IS_NOT_A_NUMBER,
    IS_NOT_IN_INTERVAL,
    THERE_ARE_NOT_ERRORS,
    TOO_FEW_ARGUMENTS
};


int Invert(int x)
{
    int base = 128;
    int res = 0;

    while (x != 0)
    {
        
        res += (x & 1) * (base);
        x >>= 1;
        base >>= 1;
    }

    return res;
}

Errors ParseArguments(int argc, char** arguments, int &number)
{
    char* stringWithDigit = arguments[1];
    size_t* errorPosition = new size_t;

    if (argc != 2)
    {
        return TOO_FEW_ARGUMENTS;
    }

    try 
    {
        number = stoi(stringWithDigit, errorPosition, 10);
    }

    catch (invalid_argument)
    {
        return IS_NOT_A_NUMBER;
    }
  
    if (stringWithDigit[*errorPosition] != '\0')
    {
        return IS_NOT_A_NUMBER;
    }

    else if (number < LOWER_LIMIT || number > UPPER_LIMIT)
    {
        return  IS_NOT_IN_INTERVAL;
    }

    else 
    {
        return THERE_ARE_NOT_ERRORS;
    }
}

int main(int argc, char** argv)
{
    int number;
    Errors errorParsedArguments;
    errorParsedArguments = ParseArguments(argc, argv, number);

    //Проверка количества агументов командной строки
    if (errorParsedArguments == TOO_FEW_ARGUMENTS)
    {
        cout << "Invalid input" << endl;
        cout << "Usage: flipbyte.exe <number>" << endl;
        return 1;
    }

    //Проверка строки на число
    if (errorParsedArguments == IS_NOT_A_NUMBER) {
        cout << "Incorrect value, second argument should be a number" << endl;
        return 1;
    }

    //Проверка числа на вхождение в интервал
    if (errorParsedArguments == IS_NOT_IN_INTERVAL) {
        cout << "Incorrect value, it should be number from 0 to 255" << endl;
        return 1;
    }

    //Получаем число путем изменения порядка битов на обратный
    number = Invert(number);
    cout << number << endl;

	return 0;
}



