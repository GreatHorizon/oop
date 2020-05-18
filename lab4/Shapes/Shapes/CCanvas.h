#pragma once
#include "../lib/include/GLFW/glfw3.h"
#include "CPoint.h"
#include "ICanvas.h"
#include <vector>
#include "../lib/include/GLFW/glfw3.h"

class CCanvas final : public ICanvas
{
public:
	void DrawLine(const CPoint& firstPoint, const CPoint& secondPoint, uint32_t lineColor) override;
	void FillPolygon(const std::vector<CPoint>& vertices, uint32_t fillColor) override;
	void DrawCircle(const CPoint& center, double radius, uint32_t lineColor) override;
	void FillCircle(const CPoint& center, double radius, uint32_t fillColor) override;
	CCanvas(GLFWwindow* window);

private:
	GLFWwindow* m_window;
	std::vector<double> GetRgb(uint32_t color);
};
