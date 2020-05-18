#include "stdafx.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CPoint.h"
#include "../Shapes/IShape.h"


struct LineSegment_
{
	const double expectedPerimeter = 5;
	const double expectedArea = 0;
	const CPoint expectedStartPoint = CPoint(6, 5);
	const CPoint expectedEndPoint = CPoint(2, 8);
	const uint32_t expectedColour = 0x00ff00;

	const CLineSegment line;

	LineSegment_()
		: line(expectedStartPoint, expectedEndPoint, expectedColour)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Line, LineSegment_)

	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const IShape*>(&line));
	}

	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_EQUAL(line.GetArea(), expectedArea);
	}

	BOOST_AUTO_TEST_CASE(has_a_perimetr)
	{
		BOOST_CHECK_EQUAL(static_cast<const IShape&>(line).GetPerimeter(), expectedPerimeter);
	}

	BOOST_AUTO_TEST_CASE(has_a_color)
	{
		BOOST_CHECK_EQUAL(static_cast<const IShape&>(line).GetOutlineColor(), expectedColour);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"(line:
	perimeter = 5.000000
	area = 0.000000
	color = 00ff00
	start point = (6.000000, 5.000000)
	end point = (2.000000, 8.000000)
)";
		BOOST_CHECK_EQUAL(static_cast<const IShape&>(line).ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()
