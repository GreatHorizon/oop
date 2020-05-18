#include "stdafx.h"
#include "ShapesControl.h"

using namespace std;

int main()
{
	ShapesControl control(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		if (!control.HandleCommand())
		{
			cout << "Incorrect command\n";
		}
	}

	if (!control.GetShapes().empty())
	{
		cout << "Shape with max area:\n" << control.FindMaxArea()->ToString();
		cout << "Shape with min perimeter:\n" << control.FindMinPerimeter()->ToString();
		control.ShowShapes();
	}
	else
	{
		cout << "Shapes list is empty\n";
	}

	return 0;
}
