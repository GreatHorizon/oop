#include "stdafx.h"
#include "CCircle.h"

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

double CCircle::GetArea() const
{
	return M_PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

std::string CCircle::ToString() const
{
	std::ostringstream strm;
	strm << "circle:\n" << std::setprecision(6) << std::fixed
		<< "\tperimeter = " << GetPerimeter() << "\n"
		<< "\tarea = " << GetArea() << "\n"
		<< "\tfill color = " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << "\n"
		<< "\toutline color = " << std::hex << std::setw(6) << std::setfill('0') << GetOutlineColor() << "\n"
		<< "\tradius = " << GetRadius() << "\n"
		<< "\tcenter = " << GetCenter().ToString() << "\n";
	return strm.str();
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
	canvas.FillCircle(m_center, m_radius, m_fillColor);
}

CCircle::CCircle(const CPoint& center, double radius, uint32_t outlieColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlieColor)
	, m_fillColor(fillColor)
{
}
