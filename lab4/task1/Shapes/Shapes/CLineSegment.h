#pragma once
#include "IShape.h"
#include "CPoint.h"
#include "ICanvas.h"

class CLineSegment final : public IShape
{
public:
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t lineColor);
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	void Draw(ICanvas& canvas) const override;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_color;
};

