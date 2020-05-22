#include "stdafx.h"
#include "../Rational/CRational.h"

BOOST_AUTO_TEST_SUITE(constructors_test)
	BOOST_AUTO_TEST_CASE(constructor_without_arguments_should_make_zero_number)
	{
		CRational number;
		BOOST_CHECK_EQUAL(number.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(
		constructor_with_one_argument_should_make_number_with_denominator_equal_to_1)
	{
		CRational number(5);
		BOOST_CHECK_EQUAL(number.GetNumerator(), 5);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(constructor_with_two_arguments_should_make_rational_fraction)
	{
		CRational number(2, 9);
		BOOST_CHECK_EQUAL(number.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 9);
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(right_binary_shift_operator_test)

	BOOST_AUTO_TEST_CASE(should_not_get_number_from_empty_stream)
	{
		CRational number;
		std::istringstream stream("");
		stream >> number;
		BOOST_CHECK_EQUAL(number.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(should_get_zero_number_when_denominator_is_zero)
	{
		CRational number;
		std::istringstream stream("-12/0");
		stream >> number;
		BOOST_CHECK_EQUAL(number.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(should_not_get_number_when_input_is_nondigit)
	{
		CRational number;
		std::istringstream stream("a/12");
		stream >> number;
		BOOST_CHECK_EQUAL(number.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(should_not_get_number_with_following_symbols_from_stream)
	{
		CRational number;
		std::istringstream stream("1/12a");
		stream >> number;
		BOOST_CHECK_EQUAL(number.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(should_get_number_from_stream_when_input_is_correct)
	{
		CRational number;
		std::istringstream stream("3/4");
		stream >> number;
		BOOST_CHECK_EQUAL(number.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 4);
	}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(normalization_test)

	BOOST_AUTO_TEST_CASE(should_remove_minus_from_denominSator)
	{
		CRational number(12, -13);
		BOOST_CHECK_EQUAL(number.GetNumerator(), -12);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 13);
	}

	BOOST_AUTO_TEST_CASE(should_divide_nomerator_and_denominator_on_gcd)
	{
		CRational firstNumber(-48, 12);
		BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), -4);
		BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 1);

		CRational secondNumber(-48, -92);		
		BOOST_CHECK_EQUAL(secondNumber.GetNumerator(), 12);
		BOOST_CHECK_EQUAL(secondNumber.GetDenominator(), 23);
	}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(to_double_test);
	BOOST_AUTO_TEST_CASE(should_return_zero_when_number_was_constructed_with_zero_arguments)
	{
		CRational number;
		BOOST_CHECK_EQUAL(number.ToDouble(), 0);
	}

	BOOST_AUTO_TEST_CASE(should_return_integer_when_number_was_constructed_with_one_arguments)
	{
		CRational number(5);
		BOOST_CHECK_EQUAL(number.ToDouble(), 5);
	}

	BOOST_AUTO_TEST_CASE(should_return_division_result_when_number_was_constructed_with_two_argument)
	{
		CRational number(5, 2);
		BOOST_CHECK_EQUAL(number.ToDouble(), 2.5);
	}

BOOST_AUTO_TEST_SUITE_END(); 


struct CRationalFixture
{
	CRational firstNumber;
	CRational secondNumber;
	CRational thirdNumber;
	CRationalFixture()
	{
		firstNumber = CRational(4, 10);
		secondNumber = CRational(8, 2);
		thirdNumber = CRational(2, 5);
	}

};

BOOST_FIXTURE_TEST_SUITE(operators_test_when_numbers_were_specified, CRationalFixture)

	BOOST_AUTO_TEST_SUITE(unary_plus_operator_test)
		BOOST_AUTO_TEST_CASE(number_should_not_change)
		{
			firstNumber = +firstNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 2);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(unary_minus_operator_test)
		BOOST_AUTO_TEST_CASE(number_should_change_numerator_sign)
		{
			firstNumber = -firstNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), -2);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}

		BOOST_AUTO_TEST_CASE(number_with_zero_value_should_not_change_sign)
		{
			CRational number;
			number = -number;
			BOOST_CHECK_EQUAL(number.GetNumerator(), 0);
			BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(left_binary_shift_operator_test)
		BOOST_AUTO_TEST_CASE(should_put_number_into_output_stream)
		{
			std::ostringstream stream;
			stream << firstNumber;
			BOOST_CHECK_EQUAL(stream.str(), "2/5\n");
		}

		BOOST_AUTO_TEST_CASE(should_put_zero_number_into_output_stream)
		{
			std::ostringstream stream;
			stream << secondNumber;
			BOOST_CHECK_EQUAL(stream.str(), "4/1\n");
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(binary_plus_operator_test)

		BOOST_AUTO_TEST_CASE(should_add_integer_to_rational_number)
		{
			firstNumber = firstNumber + 5;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 27);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}

		BOOST_AUTO_TEST_CASE(should_add_rational_number_to_integer)
		{
			firstNumber = 5 + firstNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 27);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}

		BOOST_AUTO_TEST_CASE(should_add_rational_number_to_rational_number)
		{
			firstNumber = secondNumber + thirdNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 22);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(binary_minus_operator_test)
		BOOST_AUTO_TEST_CASE(should_subtract_integer_from_rational_number)
		{
			firstNumber = firstNumber - 5;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), -23);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}

		BOOST_AUTO_TEST_CASE(should_subtract_rational_number_from_integer)
		{
			firstNumber = 5 - firstNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 23);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}

		BOOST_AUTO_TEST_CASE(should_subtract_rational_number_from_rational_number)
		{
			firstNumber = firstNumber - thirdNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 0);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 1);
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(plus_equals_operator_test)
		BOOST_AUTO_TEST_CASE(should_add_integer_to_rational_number)
		{
			firstNumber += 5;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 27);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}

		BOOST_AUTO_TEST_CASE(should_add_rational_number_to_rational_number)
		{
			firstNumber += secondNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 22);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(minus_equals_operator_test)
		BOOST_AUTO_TEST_CASE(should_add_integer_to_rational_number)
		{
			firstNumber -= 5;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), -23);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}

		BOOST_AUTO_TEST_CASE(should_add_rational_number_to_rational_number)
		{
			firstNumber -= secondNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), -18);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(multiplication_operator_test)

		BOOST_AUTO_TEST_CASE(should_multiply_integer_on_rational_number)
		{
			firstNumber = firstNumber * 5;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 2);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 1);
		}

		BOOST_AUTO_TEST_CASE(should_myltiply_rational_number_on_zero)
		{
			firstNumber = firstNumber * 0;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 0);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 1);
		}

		BOOST_AUTO_TEST_CASE(should_multiply_rational_number_on_rational_number)
		{
			firstNumber = secondNumber * firstNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 8);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(division_operator_test)

		BOOST_AUTO_TEST_CASE(should_divide_rational_number_by_integer)
		{
			firstNumber = firstNumber / 5;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 2);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 25);
		}

		BOOST_AUTO_TEST_CASE(should_divide_rational_number_by_zero)
		{
			firstNumber = firstNumber / 0;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 0);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 1);
		}

		BOOST_AUTO_TEST_CASE(should_divide_integer_by_rational_number)
		{
			firstNumber = 5 / firstNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 25);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 2);
		}

		BOOST_AUTO_TEST_CASE(should_divide_rational_number_by_rational_number)
		{
			firstNumber = firstNumber / secondNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 1);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 10);
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(multiply_equals_operator_test)
		BOOST_AUTO_TEST_CASE(should_myltiply_rational_number_on_integer)
		{
			firstNumber *= 5;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 2);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 1);
		}

		BOOST_AUTO_TEST_CASE(should_myltiply_rational_number_on_rational_number)
		{
			firstNumber *= secondNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 8);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 5);
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(divide_equals_operator_test)
		BOOST_AUTO_TEST_CASE(should_divide_rational_number_on_integer)
		{
			firstNumber /= 5;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 2);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 25);
		}

		BOOST_AUTO_TEST_CASE(should_divide_rational_number_on_rational_number)
		{
			firstNumber /= secondNumber;
			BOOST_CHECK_EQUAL(firstNumber.GetNumerator(), 1);
			BOOST_CHECK_EQUAL(firstNumber.GetDenominator(), 10);
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(equal_operator_test)

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_equal_to_rational_number)
		{
			BOOST_CHECK(firstNumber == thirdNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_false_when_rational_number_is_not_equal_to_rational_number)
		{
			BOOST_CHECK(!(firstNumber == secondNumber));
		}


		BOOST_AUTO_TEST_CASE(should_return_false_when_rational_number_is_not_equal_to_integer)
		{
			BOOST_CHECK(!(secondNumber == 5));
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(not_equal_to_operator_test)

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_is_not_equal_to_rational_number)
		{
			BOOST_CHECK(firstNumber != secondNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_false_when_integer_equal_to_rational_number)
		{
			BOOST_CHECK(!(firstNumber != thirdNumber));
		}

		BOOST_AUTO_TEST_CASE(should_return_false_when_rational_number_equal_to_integer)
		{
			BOOST_CHECK(!(secondNumber != 4));
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(greater_than_operator_test)

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_greater_than_rational_number)
		{
			BOOST_CHECK(secondNumber > firstNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_false_when_integer_less_than_rational_number)
		{
			BOOST_CHECK(!(1 > secondNumber));
		}

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_greater_than_integer)
		{
			BOOST_CHECK(secondNumber > 2);
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(less_than_operator_test)

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_less_than_rational_number)
		{
			BOOST_CHECK(firstNumber < secondNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_true_when_integer_less_than_rational_number)
		{
			BOOST_CHECK(1 < secondNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_false_when_rational_number_greater_than_integer)
		{
			BOOST_CHECK(!(secondNumber < 1));
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(less_or_equal_operator_test)

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_less_than_rational_number)
		{
			BOOST_CHECK(firstNumber <= secondNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_equal_to_rational_number)
		{
			BOOST_CHECK(firstNumber <= thirdNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_false_when_integer_less_than_rational_number)
		{
			BOOST_CHECK(!(5 <= secondNumber));
		}

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_equal_to_integer)
		{
			BOOST_CHECK(4 <= secondNumber);
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(greater_or_equal_operator_test)

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_greater_than_rational_number)
		{
			BOOST_CHECK(secondNumber >= firstNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_true_when_rational_number_equal_to_rational_number)
		{
			BOOST_CHECK(firstNumber >= thirdNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_true_when_integer_greater_than_rational_number)
		{
			BOOST_CHECK(1 >= firstNumber);
		}

		BOOST_AUTO_TEST_CASE(should_return_false_when_rational_number_equal_to_integer)
		{
			BOOST_CHECK(4 >= secondNumber);
		}
	BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(ToCompoundFraction_test)

	BOOST_AUTO_TEST_CASE(should_return_zero_integral_part_when_numerator_less_than_denominator)
	{
		CRational number(1, 9);	
		auto pair = number.ToCompoundFraction();

		BOOST_CHECK_EQUAL(pair.first, 0);
		BOOST_CHECK_EQUAL(pair.second.GetNumerator(), 1);
		BOOST_CHECK_EQUAL(pair.second.GetDenominator(), 9);
	}

	BOOST_AUTO_TEST_CASE(should_return_zero_rational_number_part_when_numerator_is_multiple_of_denominator)
	{
		CRational number(2, 1);
		auto pair = number.ToCompoundFraction();

		BOOST_CHECK_EQUAL(pair.first, 2);
		BOOST_CHECK_EQUAL(pair.second.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(pair.second.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(should_return_zero_pair_when_rational_number_is_zero)
	{
		CRational number;
		auto pair = number.ToCompoundFraction();

		BOOST_CHECK_EQUAL(pair.first, 0);
		BOOST_CHECK_EQUAL(pair.second.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(pair.second.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(should_return_zero_rational_part_when_rational_number_is_integer)
	{
		CRational number(5);
		auto pair = number.ToCompoundFraction();

		BOOST_CHECK_EQUAL(pair.first, 5);
		BOOST_CHECK_EQUAL(pair.second.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(pair.second.GetDenominator(), 1);
	}
BOOST_AUTO_TEST_SUITE_END();