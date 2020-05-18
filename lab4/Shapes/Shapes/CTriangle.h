#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle final : public ISolidShape
{
public:
	uint32_t GetFillColor() const override;
	uint32_t GetOutlineColor() const override;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	double GetAdgeLength(const CPoint& firstVertex, const CPoint& secondVertex) const;

	CTriangle(const CPoint& firstVertex, const CPoint& secondVertex, const CPoint& thirdVertex
	, uint32_t fillColor, uint32_t outlineColor);


private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};

