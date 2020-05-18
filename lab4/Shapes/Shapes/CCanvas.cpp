#include "CCanvas.h"
#include "stdafx.h"
#include "../lib/include/GLFW/glfw3.h"

void CCanvas::DrawLine(const CPoint& firstPoint, const CPoint& secondPoint, uint32_t lineColor)
{
	std::vector<double> rgb = GetRgb(lineColor);

	glLineWidth(2);
	glColor3d(rgb[0], rgb[1], rgb[2]);

	glBegin(GL_LINES);

	glVertex2d(firstPoint.GetX(), firstPoint.GetY());
	glVertex2d(secondPoint.GetX(), secondPoint.GetY());

	glEnd();

	glEnable(GL_LINE_SMOOTH);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& vertices, uint32_t fillColor)
{
	std::vector<double> rgb = GetRgb(fillColor);

	glColor3d(rgb[0], rgb[1], rgb[2]);

	glBegin(GL_POLYGON);

	for (auto& vertex : vertices)
	{
		glVertex2d(vertex.GetX(), vertex.GetY());
	}

	glEnd();
}

void CCanvas::DrawCircle(const CPoint& center, double radius, uint32_t lineColor)
{

	std::vector<double> rgb = GetRgb(lineColor);
	glLineWidth(4);
	glColor3d(rgb[0], rgb[1], rgb[2]);

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++) {
		double degInRad = i * M_PI / 180 ;
		glVertex2d((cos(degInRad) * radius) + center.GetX(), (sin(degInRad) * radius) + center.GetY());
	}

	glEnd();
	glEnable(GL_LINE_SMOOTH);
}

void CCanvas::FillCircle(const CPoint& center, double radius, uint32_t fillColor)
{
	std::vector<double> rgb = GetRgb(fillColor);
	glColor3d(rgb[0], rgb[1], rgb[2]);

	glBegin(GL_POLYGON);

	for (int i = 0; i < 360; i++) {
		double degInRad = i * M_PI / 180;
		glVertex2d((cos(degInRad) * radius) + center.GetX(), (sin(degInRad) * radius) + center.GetY());
	}

	glEnd();
}

CCanvas::CCanvas(GLFWwindow* window)
	:m_window(window)
{
}

std::vector<double> CCanvas::GetRgb(uint32_t color)
{
	std::vector<double> rgb;

	rgb.push_back(((color >> 16) & 255) / 255.0);
	rgb.push_back(((color >> 8) & 255) / 255.0);
	rgb.push_back((color & 255) / 255.0);

	return rgb;
}
