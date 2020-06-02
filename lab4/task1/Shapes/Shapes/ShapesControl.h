#pragma once
#include "IShape.h"
#include <boost/noncopyable.hpp>

class ShapesControl final : boost::noncopyable
{
public:
	ShapesControl(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void ShowShapes() const;

	std::vector<std::shared_ptr <IShape>> GetShapes() const;
	std::shared_ptr<IShape> FindMaxArea() const;
	std::shared_ptr<IShape> FindMinPerimeter() const;

private:
	bool MakeLine(std::istream& args);
	bool MakeRectangle(std::istream& args);
	bool MakeTriangle(std::istream& args);
	bool MakeCircle(std::istream& args);

private:
	typedef std::function<bool(std::istream& args)> Handler;
	typedef std::map<std::string, Handler> ActionMap;

	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::shared_ptr<IShape>> m_shapesArray;
	const ActionMap m_actionMap;
};

