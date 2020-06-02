#include "CPoint.h"

CPoint::CPoint(double xCoord, double yCoord)
	: x(xCoord)
	, y(yCoord)
{
}

double CPoint::GetX() const
{
	return x;
}

double CPoint::GetY() const
{
	return y;
}

std::string CPoint::ToString() const
{
	return "(" + std::to_string(x)
		+ ", " + std::to_string(y) + ")";
}

