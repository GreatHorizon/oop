#pragma once
#include "CPoint.h"
#include "include/GLFW/glfw3.h"
#include <cstdint>
#include <vector>


class ICanvas
{
public:
	virtual void DrawLine(const CPoint& firstPoint, const CPoint& secondPoint, uint32_t lineColor) = 0;
	virtual void FillPolygon(const std::vector<CPoint>&, uint32_t fillColor) = 0;
	virtual void DrawCircle(const CPoint& center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(const CPoint& center, double radius, uint32_t lineColor) = 0;
	virtual ~ICanvas() {}
};