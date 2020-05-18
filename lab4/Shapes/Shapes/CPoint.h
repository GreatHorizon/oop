#pragma once
#include <string>

class CPoint final
{
public:
	CPoint(double xCoord, double yCoord);
	double GetX() const;
	double GetY() const;
	std::string ToString() const;

private:
	double x;
	double y;
};

