#include "stdafx.h"
#include "../Shapes/CCircle.h"
#include "../Shapes/CPoint.h"

#define _USE_MATH_DEFINES

struct Circle_
{
	const double expectedPerimeter = 62.831853;
	const double expectedArea = 314.159265;
	const uint32_t expectedFillColour = 0xFFFF00;
	const uint32_t expectedOutlineColour = 0xF08080;
	const double radius = 10;
	const CPoint center = CPoint(3, 3);
	const CCircle circle;

	Circle_()
		: circle(center, radius, 
			expectedOutlineColour, expectedFillColour)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Circle, Circle_)

	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const IShape*>(&circle));
	}

	BOOST_AUTO_TEST_CASE(is_a_solid_shape)
	{
		BOOST_CHECK(static_cast<const ISolidShape*>(&circle));
	}


	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const IShape&>(circle).GetPerimeter(), expectedPerimeter, 1e-7);
	}


	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const IShape&>(circle).GetArea(), expectedArea, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK_EQUAL(static_cast<const IShape&>(circle).GetOutlineColor(), expectedOutlineColour);
	}

	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(static_cast<const ISolidShape&>(circle).GetFillColor(), expectedFillColour);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"(circle:
	perimeter = 62.831853
	area = 314.159265
	fill color = ffff00
	outline color = f08080
	radius = 10.000000
	center = (3.000000, 3.000000)
)";
		BOOST_CHECK_EQUAL(static_cast<const ISolidShape&>(circle).ToString(), expectedString);
	}

BOOST_AUTO_TEST_SUITE_END()