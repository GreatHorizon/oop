#include "CTriangle.h"
#include "stdafx.h"

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

double CTriangle::GetArea() const
{
	double a = GetAdgeLength(m_vertex1, m_vertex2);
	double b = GetAdgeLength(m_vertex3, m_vertex2);
	double c = GetAdgeLength(m_vertex3, m_vertex1);
	double perimeterHalf = (a + b + c) /2 ;
	return sqrt(perimeterHalf * (perimeterHalf - a) * (perimeterHalf - b) * (perimeterHalf - c));
}

double CTriangle::GetPerimeter() const
{
	return GetAdgeLength(m_vertex1, m_vertex2) 
		+ GetAdgeLength(m_vertex1, m_vertex3)
		+ GetAdgeLength(m_vertex2, m_vertex3);
}

double CTriangle::GetAdgeLength(const CPoint& firstVertex, const CPoint& secondVertex) const
{
	return sqrt(pow(firstVertex.GetX() - secondVertex.GetX(), 2) + pow(firstVertex.GetY() - secondVertex.GetY(), 2));
}

std::string CTriangle::ToString() const
{
	std::ostringstream strm;
	strm << "triangle:\n" << std::setprecision(6) << std::fixed
		<< "\tperimeter = " << GetPerimeter() << "\n"
		<< "\tarea = " << GetArea() << "\n"
		<< "\tfill color = " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << "\n"
		<< "\toutline color = " << std::hex << std::setw(6) << std::setfill('0') << GetOutlineColor() << "\n"
		<< "\tvertex1 = " << GetVertex1().ToString() << "\n"
		<< "\tvertex2 = " << GetVertex2().ToString() << "\n"
		<< "\tvertex3 = " << GetVertex3().ToString() << "\n";

	return strm.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> vertices =
	{
		m_vertex1,
		m_vertex2,
		m_vertex3
	};

	canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);

	canvas.FillPolygon(vertices, m_fillColor);
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

CTriangle::CTriangle(const CPoint& firstVertex, const CPoint& secondVertex,
	const CPoint& thirdVertex, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(firstVertex)
	, m_vertex2(secondVertex)
	, m_vertex3(thirdVertex)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}
