#include "stdafx.h"
#include "ShapesControl.h"

using namespace std;

int main()
{
	ShapesControl control(cin, cout);

	cout << "Commands:\n"
		<< "line <first point X> <first point Y> <second point X> <second point Y> <line color>\n"
		<< "circle <center point X> <center Point Y> <outline color> <fill color>\n"
		<< "rectangle <left top point X> <left top point Y> <width> <height> <outline color> <fill color>\n"
		<< "triangle <vertex1 X> <vertex1 Y> <vertex2 X> <vertex2 Y> <vertex3 X> <vertex3 Y> <outline color> <fill color>\n\n";

	while (!cin.eof() && !cin.fail())
	{
		cout << ">";
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
