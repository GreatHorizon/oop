#include "stdafx.h"
#include "../Shapes/ShapesControl.h"

struct ShapesControlDependancies
{
	std::stringstream input;
	std::stringstream output;
};

struct ShapesControlFixture: ShapesControlDependancies
{
	 ShapesControl shapesControl;

	 ShapesControlFixture()
		: shapesControl(input, output)
	{
	};

	void VerifyCommandHandling(const std::string& command, const std::string& expectedOutput)
	{
		output = std::stringstream();
		input = std::stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(shapesControl.HandleCommand());
		BOOST_CHECK(input.eof());	
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void CheckShape(const std::string& expectedString)
	{
		auto shapes = shapesControl.GetShapes();
		BOOST_CHECK_EQUAL(shapes.front()->ToString(), expectedString);
	}

	void CheckOutputAfterCommand(const std::string& expectedString)
	{
		BOOST_CHECK_EQUAL(output.str(), expectedString);
	}

	void CheckHandleCommandFunction(const std::string& command, bool result)
	{
		output = std::stringstream();
		input = std::stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK_EQUAL(shapesControl.HandleCommand(), result);
	}

	void ExecuteCommand(const std::string command)
	{
		output = std::stringstream();
		input = std::stringstream();
		BOOST_CHECK(input << command);
		shapesControl.HandleCommand();
		BOOST_CHECK(input.eof());
	}

};

BOOST_FIXTURE_TEST_SUITE(ShapesControl_test, ShapesControlFixture)

	BOOST_AUTO_TEST_SUITE(handle_command_test)
		BOOST_AUTO_TEST_CASE(cant_process_invalid_command)
		{
			CheckHandleCommandFunction("va", false);
		};

		BOOST_AUTO_TEST_CASE(can_process_valid_command)
		{
			CheckHandleCommandFunction("line", true);
		};

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(make_line_test)
		BOOST_AUTO_TEST_CASE(cant_process_command_with_incorrect_arguments)
		{
			VerifyCommandHandling("line asd asd ffffff", "Incorrect input\n");
			VerifyCommandHandling("line asd ffffff", "Incorrect input\n");
			VerifyCommandHandling("line 10 20 asd ffffff", "Incorrect input\n");
		};

		BOOST_AUTO_TEST_CASE(cant_process_command_with_empty_arguments)
		{
			VerifyCommandHandling("line", "Incorrect input\n");
		};

		BOOST_AUTO_TEST_CASE(can_make_line_with_correct_arguments)
		{
			const std::string expectedString = R"(line:
	perimeter = 6.403124
	area = 0.000000
	color = ffffff
	start point = (2.000000, 7.000000)
	end point = (7.000000, 3.000000)
)";
			VerifyCommandHandling("line 2 7 7 3 ffffff", "");
			CheckShape(expectedString);
		};

	BOOST_AUTO_TEST_SUITE_END();


	BOOST_AUTO_TEST_SUITE(make_rectangle_test)
		BOOST_AUTO_TEST_CASE(cant_process_command_with_incorrect_arguments)
		{
			VerifyCommandHandling("rectangle asd asd ffffff", "Incorrect input\n");
			VerifyCommandHandling("rectangle 10 12 asds asd ffffff", "Incorrect input\n");
			VerifyCommandHandling("rectangle 10 12 20 asd ffffff", "Incorrect input\n");
			VerifyCommandHandling("rectangle asd ffffff", "Incorrect input\n");
			VerifyCommandHandling("rectangle 10asd 10 12 11", "Incorrect input\n");
		};

		BOOST_AUTO_TEST_CASE(cant_process_command_with_empty_arguments)
		{
			VerifyCommandHandling("rectangle", "Incorrect input\n");
		};


		BOOST_AUTO_TEST_CASE(can_make_rectangle_with_correct_arguments)
		{
			const auto expectedString = R"(rectangle:
	perimeter = 18.000000
	area = 20.000000
	fill color = ffff00
	outline color = f08080
	left top point = (2.000000, 7.000000)
	right bottom point = (7.000000, 3.000000)
)";
			VerifyCommandHandling("rectangle 2 7 5 4 f08080 ffff00" , "");
			CheckShape(expectedString);
		};
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(make_circle_test)
		BOOST_AUTO_TEST_CASE(cant_process_command_with_incorrect_arguments)
		{
			VerifyCommandHandling("circle 10 12 10a ffffff 00ff00", "Incorrect input\n");
			VerifyCommandHandling("circle 1s0as 12 9  ffffff 00ff00", "Incorrect input\n");
			VerifyCommandHandling("circle 12 asd f ffffff 00ff00", "Incorrect input\n");
		};

	BOOST_AUTO_TEST_CASE(cant_process_command_with_empty_arguments)
	{
		VerifyCommandHandling("circle", "Incorrect input\n");
	};


	BOOST_AUTO_TEST_CASE(can_make_circle_with_correct_arguments)
	{
		const auto expectedString = R"(circle:
	perimeter = 62.831853
	area = 314.159265
	fill color = ffff00
	outline color = f08080
	radius = 10.000000
	center = (3.000000, 3.000000)
)";
		VerifyCommandHandling("circle 3 3 10 f08080 ffff00", "");
		CheckShape(expectedString);
	};
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(make_triangle_test)
		BOOST_AUTO_TEST_CASE(cant_process_command_with_incorrect_arguments)
		{
			VerifyCommandHandling("triangle 10 12 asd asd 12 10 ffffff 00ff00", "Incorrect input\n");
			VerifyCommandHandling("triangle 10 12 9 10 12a 10 ffffff 00ff00", "Incorrect input\n");
			VerifyCommandHandling("triangle a 12 asd 10 12 10 ffffff 00ff00", "Incorrect input\n");
		};

		BOOST_AUTO_TEST_CASE(cant_process_command_with_empty_arguments)
		{
			VerifyCommandHandling("triangle", "Incorrect input\n");
		};


		BOOST_AUTO_TEST_CASE(can_make_triangle_with_correct_arguments)
		{
			const auto expectedString = R"(triangle:
	perimeter = 18.810250
	area = 15.000000
	fill color = ffff00
	outline color = f08080
	vertex1 = (3.000000, 3.000000)
	vertex2 = (3.000000, 8.000000)
	vertex3 = (9.000000, 3.000000)
)";
			VerifyCommandHandling("triangle 3 3 3 8 9 3 f08080 ffff00", "");
			CheckShape(expectedString);
		};
	BOOST_AUTO_TEST_SUITE_END();

	struct when_shapes_were_defined_ : ShapesControlFixture
	{
		when_shapes_were_defined_()
		{
			ExecuteCommand("triangle 3 8 9 3 3 3 ffffff 00ff00");
			ExecuteCommand("line 10 12 10 20 00ff00");
			ExecuteCommand("rectangle 3 12 5 10 ffffff 00ff00");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(find_shapes_test, when_shapes_were_defined_)

		BOOST_AUTO_TEST_CASE(can_find_shape_with_max_area)
		{
			std::string expectedstring = R"(rectangle:
	perimeter = 30.000000
	area = 50.000000
	fill color = 00ff00
	outline color = ffffff
	left top point = (3.000000, 12.000000)
	right bottom point = (8.000000, 2.000000)
)";
			BOOST_CHECK_EQUAL(shapesControl.FindMaxArea()->ToString(), expectedstring);
		}

		BOOST_AUTO_TEST_CASE(can_find_shape_with_min_perimeter)
		{
			std::string expectedstring = R"(line:
	perimeter = 8.000000
	area = 0.000000
	color = 00ff00
	start point = (10.000000, 12.000000)
	end point = (10.000000, 20.000000)
)";
			BOOST_CHECK_EQUAL(shapesControl.FindMinPerimeter()->ToString(), expectedstring);
		}

	BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();

