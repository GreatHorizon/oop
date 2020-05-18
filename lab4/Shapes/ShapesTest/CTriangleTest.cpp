#include "stdafx.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/CPoint.h"

#define _USE_MATH_DEFINES

struct Triangle_
{
	const double expectedPerimeter = 13.300563;
	const double expectedArea = 6;
	const double expectedWidth = 5;
	const double expectedHeigth = 4;
	const uint32_t expectedFillColour = 0xFFFF00;
	const uint32_t expectedOutlineColour = 0xF08080;
	const CPoint firstVertex = CPoint(3, 3);
	const CPoint secondVertex = CPoint(5, 5);
	const CPoint thirdVertex = CPoint(9, 3);
	const CTriangle triangle;

	Triangle_()
		: triangle(firstVertex, secondVertex, thirdVertex,
			expectedOutlineColour, expectedFillColour)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)

	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const IShape*>(&triangle));
	}

	BOOST_AUTO_TEST_CASE(is_a_solid_shape)
	{
		BOOST_CHECK(static_cast<const ISolidShape*>(&triangle));
	}

	
	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const IShape&>(triangle).GetPerimeter(), expectedPerimeter, 1e-7);
	}

	
	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const IShape&>(triangle).GetArea(), expectedArea, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK_EQUAL(static_cast<const IShape&>(triangle).GetOutlineColor(), expectedOutlineColour);
	}

	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(static_cast<const ISolidShape&>(triangle).GetFillColor(), expectedFillColour);
	}	

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"(triangle:
	perimeter = 13.300563
	area = 6.000000
	fill color = ffff00
	outline color = f08080
	vertex1 = (3.000000, 3.000000)
	vertex2 = (5.000000, 5.000000)
	vertex3 = (9.000000, 3.000000)
)";
		BOOST_CHECK_EQUAL(static_cast<const ISolidShape&>(triangle).ToString(), expectedString);
	}

BOOST_AUTO_TEST_SUITE_END()