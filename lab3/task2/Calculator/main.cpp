#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorControl.h"
#include "ValueHolder.h"

using namespace std;

int main()
{
	CCalculator calculator;
	CCalculatorControl CalculatorControl(calculator, cin, cout);

	while (!cin.eof())
	{
		cout << ">";
		if (!CalculatorControl.HandleCommand())
		{
			cout << "Invalid command\n";
		}
	}

	return 0;
}