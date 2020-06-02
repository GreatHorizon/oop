#include "stdafx.h"
#include "CRectangle.h"
#include "CPoint.h"

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTopPoint.GetX() + this->m_width, m_leftTopPoint.GetY() - this->m_height);
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_height + m_width) * 2;
}

std::string CRectangle::ToString() const
{
	std::ostringstream strm;
	strm << "rectangle:\n" << std::setprecision(6) << std::fixed
		<< "\tperimeter = " << GetPerimeter() << "\n"
		<< "\tarea = " << GetArea() << "\n"
		<< "\tfill color = " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << "\n"
		<< "\toutline color = " << std::hex << std::setw(6) << std::setfill('0') << GetOutlineColor() << "\n"
		<< "\tleft top point = " << m_leftTopPoint.ToString() << "\n"
		<< "\tright bottom point = " << GetRightBottom().ToString() << "\n";

	return strm.str();
}

void CRectangle::Draw(ICanvas& canvas) const
{
	CPoint rightTopPoint(m_leftTopPoint.GetX() + m_width, m_leftTopPoint.GetY());
	CPoint leftBottomPoint(m_leftTopPoint.GetX(), m_leftTopPoint.GetY() - m_height);
	std::vector<CPoint> vertices =
	{
		m_leftTopPoint,
		rightTopPoint,
		GetRightBottom(),
		leftBottomPoint
	};

	canvas.DrawLine(m_leftTopPoint, leftBottomPoint, m_outlineColor);
	canvas.DrawLine(leftBottomPoint, GetRightBottom(), m_outlineColor);
	canvas.DrawLine(GetRightBottom(), rightTopPoint, m_outlineColor);
	canvas.DrawLine(rightTopPoint, m_leftTopPoint, m_outlineColor);

	canvas.FillPolygon(vertices, m_fillColor);
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

CRectangle::CRectangle(const CPoint& leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTopPoint(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
