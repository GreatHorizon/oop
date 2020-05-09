#include "stdafx.h"
#include "../Calculator/Calculator.h"
#include "../Calculator/ValueHolder.h"

enum class Operation;

using namespace std;

struct CalculatorFixture
{
	CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(Calculator, CalculatorFixture)
	BOOST_AUTO_TEST_SUITE(add_variable_test)

		BOOST_AUTO_TEST_CASE(cant_add_incorrect_variable_name) 
		{
			BOOST_CHECK_EQUAL(calculator.AddVariable("1var"), false);	
			BOOST_CHECK_EQUAL(calculator.AddVariable("var**"), false);	
			BOOST_CHECK_EQUAL(calculator.AddVariable(""), false);	
			BOOST_CHECK_EQUAL(calculator.AddVariable("ôûâ"), false);	
		}
		
		BOOST_AUTO_TEST_CASE(can_add_variable_with_correct_name)
		{
			BOOST_CHECK_EQUAL(calculator.AddVariable("ch1"), true);
		}

		BOOST_AUTO_TEST_CASE(cant_add_variable_with_name_already_taken)
		{
			calculator.AddVariable("ch1");
			BOOST_CHECK_EQUAL(calculator.AddVariable("ch1"), false);
		}

	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(assign_value_to_variable_test)
		BOOST_AUTO_TEST_CASE(cant_assign_value_to_incorrect_variable)
		{
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("1ch", "10"), false);
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("**", "10"), false);
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("", "10"), false);
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("ôûâ", "10"), false);
		}
		
		BOOST_AUTO_TEST_CASE(can_assign_value_to_variable)
		{
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("ch1", "10"), true);
		}

		BOOST_AUTO_TEST_CASE(can_assign_variable_value_to_variable)
		{
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("ch1", "10"), true);
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("ch2", "ch1"), true);
		}

		BOOST_AUTO_TEST_CASE(cant_assign_incorrect_value_to_variable)
		{
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("ch1", "aa"), false);
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("ch1", "12aas"), false);
		}

		BOOST_AUTO_TEST_CASE(cant_assign_unassigned_variable_to_variable)
		{
			calculator.AddVariable("ch1");
			BOOST_CHECK_EQUAL(calculator.AssignValueToVariable("ch1", "ch2"), false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	

	struct when_variables_were_defined_ : CalculatorFixture
	{
		when_variables_were_defined_()
		{
			calculator.AssignValueToVariable("x", "10.55");
			calculator.AssignValueToVariable("y", "9.45");
			calculator.AssignValueToVariable("z", "5");
			calculator.AddVariable("k");
			calculator.AddVariable("m");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_variables_were_defined, when_variables_were_defined_)
		BOOST_AUTO_TEST_SUITE(define_function_test)
			BOOST_AUTO_TEST_CASE(cant_define_function_with_undefined_variables)
			{
				BOOST_CHECK_EQUAL(calculator.DefineFunction("fn", "ch1", "ch2", Operation::ADDITION), false);
				BOOST_CHECK_EQUAL(calculator.DefineFunction("fn", "ch1", "", Operation::NONE), false);
				auto valueMap = calculator.GetValueMap();
				auto function = valueMap.find("f1");
				BOOST_CHECK(function == valueMap.end());
			}

			BOOST_AUTO_TEST_CASE(cant_define_function_with_incorrect_name)
			{
				BOOST_CHECK_EQUAL(calculator.DefineFunction("!f", "ch1", "ch2", Operation::ADDITION), false);
				auto valueMap = calculator.GetValueMap();
				auto function = valueMap.find("!f");
				BOOST_CHECK(function == valueMap.end());
			}

			BOOST_AUTO_TEST_CASE(can_define_function)
			{
				BOOST_CHECK_EQUAL(calculator.DefineFunction("f", "k", "m", Operation::ADDITION), true);
				BOOST_CHECK_EQUAL(calculator.DefineFunction("f1", "x", "y", Operation::MULTIPLICATION), true);
				BOOST_CHECK_EQUAL(calculator.DefineFunction("f2", "y", "y", Operation::MULTIPLICATION), true);
				BOOST_CHECK_EQUAL(calculator.DefineFunction("f3", "y", "x", Operation::DIVISION), true);
				BOOST_CHECK_EQUAL(calculator.DefineFunction("f4", "m", "", Operation::NONE), true);
				BOOST_CHECK_EQUAL(calculator.DefineFunction("f5", "x", "", Operation::NONE), true);

				auto valueMap = calculator.GetValueMap();
				BOOST_CHECK(valueMap.find("f") != valueMap.end());
				BOOST_CHECK(valueMap.find("f1") != valueMap.end());
				BOOST_CHECK(valueMap.find("f2") != valueMap.end());
				BOOST_CHECK(valueMap.find("f3") != valueMap.end());
				BOOST_CHECK(valueMap.find("f4") != valueMap.end());
				BOOST_CHECK(valueMap.find("f5") != valueMap.end());
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(update_function_value)
			BOOST_AUTO_TEST_CASE(should_update_function_value_if_variables_changed)
			{
				calculator.DefineFunction("XPLUSY", "x", "y", Operation::ADDITION);
				calculator.DefineFunction("XPLUSZ", "x", "z", Operation::ADDITION);
				auto valueMap = calculator.GetValueMap();
				auto function = valueMap.find("XPLUSY");			
				BOOST_CHECK_EQUAL(function->second->GetValue().value(), 20);
				function = valueMap.find("XPLUSZ");
				BOOST_CHECK_EQUAL(function->second->GetValue().value(), 15.55);

				calculator.AssignValueToVariable("x", "0.55");
				calculator.UpdateFunctionValue("x");
				valueMap = calculator.GetValueMap();
				function = valueMap.find("XPLUSY");
				BOOST_CHECK_EQUAL(function->second->GetValue().value(), 10);
				function = valueMap.find("XPLUSZ");
				BOOST_CHECK_EQUAL(function->second->GetValue().value(), 5.55);
			}
			
			BOOST_AUTO_TEST_CASE(should_update_depending_function_value_if_function_changed)
			{
				calculator.DefineFunction("XPLUSY", "x", "y", Operation::ADDITION);
				calculator.DefineFunction("XPLUSYMINUSZ", "XPLUSY", "z", Operation::SUBTRACTION);
				auto valueMap = calculator.GetValueMap();
				auto function = valueMap.find("XPLUSY");
				BOOST_CHECK_EQUAL(function->second->GetValue().value(), 20);

				function = valueMap.find("XPLUSYMINUSZ");
				BOOST_CHECK_EQUAL(function->second->GetValue().value(), 15);

				calculator.AssignValueToVariable("x", "0.55");
				calculator.UpdateFunctionValue("x");
				valueMap = calculator.GetValueMap();
				function = valueMap.find("XPLUSY");
				BOOST_CHECK_EQUAL(function->second->GetValue().value(), 10);

				function = valueMap.find("XPLUSYMINUSZ");
				BOOST_CHECK_EQUAL(function->second->GetValue().value(), 5);
			}

			BOOST_AUTO_TEST_CASE(should_set_value_after_assigning_variable)
			{
				calculator.DefineFunction("f1", "k", "", Operation::NONE);
				auto valueMap = calculator.GetValueMap();
				auto function = valueMap.find("f1");
				BOOST_CHECK(!function->second->GetValue());

				calculator.AssignValueToVariable("k", "5");
				calculator.UpdateFunctionValue("k");
				valueMap = calculator.GetValueMap();
				function = valueMap.find("f1");
				BOOST_CHECK_EQUAL(function->second->GetValue().value(), 5);

			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()