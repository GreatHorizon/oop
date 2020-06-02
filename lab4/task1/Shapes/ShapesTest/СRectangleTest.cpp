#include "stdafx.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CPoint.h"

struct Rectangle_
{
	const double expectedPerimeter = 18;
	const double expectedArea = 20;
	const double expectedWidth = 5;
	const double expectedHeigth = 4;
	const uint32_t expectedFillColour = 0xFFFF00;
	const uint32_t expectedOutlineColour = 0xF08080;
	const CPoint expectedLeftTopPoint = CPoint(2, 7);
	const CPoint expectedRightBottomPoint = CPoint(7, 3);
	const CRectangle rectangle;

	Rectangle_()
		: rectangle(expectedLeftTopPoint, expectedWidth, expectedHeigth,
			expectedOutlineColour, expectedFillColour)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Rectangel, Rectangle_)

	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const IShape*>(&rectangle));
	}

	BOOST_AUTO_TEST_CASE(is_a_solid_shape)
	{
		BOOST_CHECK(static_cast<const ISolidShape*>(&rectangle));
	}

	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<const IShape&>(rectangle).GetPerimeter(), expectedPerimeter);
	}

	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_EQUAL(static_cast<const IShape&>(rectangle).GetArea(), expectedArea);
	}

	BOOST_AUTO_TEST_CASE(has_height)
	{
		BOOST_CHECK_EQUAL(rectangle.GetHeight(), expectedHeigth);
	}

	BOOST_AUTO_TEST_CASE(has_width)
	{
		BOOST_CHECK_EQUAL(rectangle.GetWidth(), expectedWidth);
	}

	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK_EQUAL(static_cast<const IShape&>(rectangle).GetOutlineColor(), expectedOutlineColour);
	}

	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(static_cast<const ISolidShape&>(rectangle).GetFillColor(), expectedFillColour);
	}

	BOOST_AUTO_TEST_CASE(has_a_right_bottom)
	{
		auto rightBottomPoint = rectangle.GetRightBottom();
		BOOST_CHECK_EQUAL(rightBottomPoint.GetX(), expectedRightBottomPoint.GetX());
		BOOST_CHECK_EQUAL(rightBottomPoint.GetY(), expectedRightBottomPoint.GetY());
	}

	BOOST_AUTO_TEST_CASE(has_a_left_top)
	{
		auto leftTop = rectangle.GetLeftTop();
		BOOST_CHECK_EQUAL(leftTop.GetX(), expectedLeftTopPoint.GetX());
		BOOST_CHECK_EQUAL(leftTop.GetY(), expectedLeftTopPoint.GetY());
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"(rectangle:
	perimeter = 18.000000
	area = 20.000000
	fill color = ffff00
	outline color = f08080
	left top point = (2.000000, 7.000000)
	right bottom point = (7.000000, 3.000000)
)";
		BOOST_CHECK_EQUAL(static_cast<const ISolidShape&>(rectangle).ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()