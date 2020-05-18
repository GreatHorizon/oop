#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
class CCircle final : public ISolidShape
{
public:
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

	CPoint GetCenter() const;
	double GetRadius() const;
	CCircle(const CPoint& center, double radius, uint32_t outlieColor, uint32_t fillColor);

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;

};

