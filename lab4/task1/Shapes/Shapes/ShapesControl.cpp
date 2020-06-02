#include "stdafx.h"
#include "ShapesControl.h"
#include "CPoint.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "CCanvas.h"
#include "include/GLFW/glfw3.h"

using namespace std;
using namespace std::placeholders;

ShapesControl::ShapesControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap(
		{
			{"line", bind(&ShapesControl::MakeLine, this, _1)},
			{"rectangle", bind(&ShapesControl::MakeRectangle, this, _1)},
			{"triangle", bind(&ShapesControl::MakeTriangle, this, _1)},
			{"circle", bind(&ShapesControl::MakeCircle, this, _1)},
		})
{
}

bool ShapesControl::HandleCommand()
{
	string consoleLine;
	getline(m_input, consoleLine);
	istringstream stream(consoleLine);

	string action;
	stream >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(stream);
	}

	return false;
}

std::optional<double> ConvertDigitStringIntoNumber(const std::string& valueLine)
{
	double number = 0;
	size_t stoppedAt;
	try
	{
		number = stod(valueLine, &stoppedAt);
	}
	catch (const std::exception&)
	{
		return std::nullopt;
	}

	if (valueLine[stoppedAt] != '\0')
	{
		return std::nullopt;
	}

	return number;
}

std::optional<std::pair<double, double>>
ParseCoords(const std::string& xValue, const std::string& yValue)
{
	if (xValue.empty() || yValue.empty())
	{
		return nullopt;
	}

	auto xCoord = ConvertDigitStringIntoNumber(xValue);
	auto yCoord = ConvertDigitStringIntoNumber(yValue);

	if (xCoord && yCoord)
	{
		return make_pair(xCoord.value(), yCoord.value());
	}

	return nullopt;
}

bool ShapesControl::MakeLine(std::istream& args)
{
	string xValue, yValue;
	uint32_t color;

	args >> xValue >> yValue;

	auto firstCoordsPair = ParseCoords(xValue, yValue);
	if (!firstCoordsPair)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	args >> xValue >> yValue;

	auto secondCoordsPair = ParseCoords(xValue, yValue);
	if (!secondCoordsPair)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	args >> hex >> color;

	CPoint firstPoint(firstCoordsPair.value().first, firstCoordsPair.value().second);
	CPoint secondtPoint(secondCoordsPair.value().first, secondCoordsPair.value().second);

	m_shapesArray.push_back(std::make_shared<CLineSegment>(firstPoint, secondtPoint, color));

	return true;
}

bool ShapesControl::MakeRectangle(std::istream& args)
{
	string argument, xValue, yValue;

	args >> xValue >> yValue;

	auto coords = ParseCoords(xValue, yValue);
	if (!coords)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	args >> argument;
	auto width = ConvertDigitStringIntoNumber(argument);
	if (!width)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	args >> argument;
	auto height = ConvertDigitStringIntoNumber(argument);
	if (!height)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	
	uint32_t outlineColor;
	uint32_t fillColor;
	args >> hex >> outlineColor >> fillColor;

	CPoint leftTopPoint(coords.value().first, coords.value().second);
	m_shapesArray.push_back(std::make_shared<CRectangle>(leftTopPoint, width.value(), 
		height.value(), outlineColor, fillColor));

	return true;
}

bool ShapesControl::MakeTriangle(std::istream& args)
{
	string xValue, yValue;

	args >> xValue >> yValue;

	auto firstVertexCoords = ParseCoords(xValue, yValue);
	if (!firstVertexCoords)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	args >> xValue >> yValue;

	auto secondVertexCoords = ParseCoords(xValue, yValue);
	if (!secondVertexCoords)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	args >> xValue >> yValue;

	auto thirdVertexCoords = ParseCoords(xValue, yValue);
	if (!thirdVertexCoords)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	uint32_t outlineColor;
	uint32_t fillColor;
	args >> hex >> outlineColor >> fillColor;

	CPoint vertex1(firstVertexCoords.value().first, firstVertexCoords.value().second);
	CPoint vertex2(secondVertexCoords.value().first, secondVertexCoords.value().second);
	CPoint vertex3(thirdVertexCoords.value().first, thirdVertexCoords.value().second);

	m_shapesArray.push_back(std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));
	return true;
}

bool ShapesControl::MakeCircle(std::istream& args)
{
	string xValue, yValue, argument;
	
	args >> xValue >> yValue;

	auto centerCoords = ParseCoords(xValue, yValue);
	if (!centerCoords)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	args >> argument;
	auto radius = ConvertDigitStringIntoNumber(argument);
	if (!radius)
	{
		m_output << "Incorrect input\n";
		return true;
	}

	uint32_t outlineColor;
	uint32_t fillColor;

	args >> hex >> outlineColor >> fillColor;

	CPoint center(centerCoords.value().first, centerCoords.value().second);
	m_shapesArray.push_back(std::make_shared<CCircle>(center, radius.value(), outlineColor, fillColor));
	return true;
}

std::shared_ptr<IShape> ShapesControl::FindMaxArea() const
{
	vector<double> areas;
	for (auto shape : m_shapesArray)
	{
		areas.push_back(shape->GetArea());
	}

	auto maxAreaIndex = std::max_element(areas.begin(), areas.end()) - areas.begin();

	return m_shapesArray[maxAreaIndex];
}

std::shared_ptr<IShape> ShapesControl::FindMinPerimeter() const
{
	vector<double> areas;
	for (auto shape : m_shapesArray)
	{
		areas.push_back(shape->GetPerimeter());
	}

	auto maxAreaIndex = std::min_element(areas.begin(), areas.end()) - areas.begin();

	return m_shapesArray[maxAreaIndex];
}

void ShapesControl::ShowShapes() const
{
	if (!glfwInit()) {
		return;
	}

	GLFWwindow* window = glfwCreateWindow(940, 780, "Shapes", NULL, NULL);
	CCanvas canvas(window);

	if (!window) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);
		for (auto shape: m_shapesArray)
		{
			shape->Draw(canvas);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

std::vector<std::shared_ptr<IShape>> ShapesControl::GetShapes() const
{
	return m_shapesArray;
}