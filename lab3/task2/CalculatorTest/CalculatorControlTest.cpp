#include "stdafx.h"
#include "../Calculator/Calculator.h"
#include "../Calculator/CalculatorControl.h"
#include "../Calculator/ValueHolder.h"

using namespace std;
enum class Operation;

struct CalculatorControlDependencies
{
	CCalculator calculator;
	stringstream input;
	stringstream output;
};

struct CalculatorControlFixture : CalculatorControlDependencies
{
	CCalculatorControl calculatorControl;

	CalculatorControlFixture()
		: calculatorControl(calculator, input, output)
	{
	};

	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(calculatorControl.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void CheckHandleCommandFunction(const string& command, bool result)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK_EQUAL(calculatorControl.HandleCommand(), result);
	};

	void ExecuteCommand(const string& command)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		calculatorControl.HandleCommand();
		BOOST_CHECK(input.eof());
	};

};

BOOST_FIXTURE_TEST_SUITE(CalculatorControl_test, CalculatorControlFixture)

	BOOST_AUTO_TEST_SUITE(handle_command_test)
		BOOST_AUTO_TEST_CASE(cant_process_invalid_command)
		{
			CheckHandleCommandFunction("va", false);
		};

		BOOST_AUTO_TEST_CASE(can_process_valid_command)
		{
			CheckHandleCommandFunction("var", true);
		};

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(define_variable_test)

		BOOST_AUTO_TEST_CASE(can_save_correct_identifier)
		{
			VerifyCommandHandling("var a1", "");
			VerifyCommandHandling("var dog_", "");
			VerifyCommandHandling("var m_a", "");
		}

		BOOST_AUTO_TEST_CASE(cant_save_incorrect_identifier)
		{
			VerifyCommandHandling("var a()", "Variable cant be created\n");
			VerifyCommandHandling("var τττ1", "Variable cant be created\n");
			VerifyCommandHandling("var", "Variable cant be created\n");
		}

		BOOST_AUTO_TEST_CASE(cant_save_identifier_with_name_already_taken)
		{
			ExecuteCommand("var ch1");
			VerifyCommandHandling("var ch1", "Variable cant be created\n");
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(assign_variable_test)
		BOOST_AUTO_TEST_CASE(can_assign_value_to_nonexistent_variable)
		{
			VerifyCommandHandling("let ch1=10.2", "");
		}

		BOOST_AUTO_TEST_CASE(cant_assign_incorrect_variable)
		{
			VerifyCommandHandling("let 1ch=10.2", "Variable cant be assigned\n");
		}

		BOOST_AUTO_TEST_CASE(can_assign_variable_value_to_variable)
		{
			ExecuteCommand("let ch1=10.23");
			ExecuteCommand("let ch2=2.5");
			VerifyCommandHandling("let ch1=ch2", "");
		}

		BOOST_AUTO_TEST_CASE(cant_assign_nonexistent_value_to_variable)
		{
			VerifyCommandHandling("let ch1=ch2", "Variable cant be assigned\n");
		}

		BOOST_AUTO_TEST_CASE(cant_assign_incorrect_value_to_variable)
		{
			VerifyCommandHandling("let ch1=10.23a", "Variable cant be assigned\n");
			VerifyCommandHandling("let ch1=aaa", "Variable cant be assigned\n");
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(define_function_test)
		BOOST_AUTO_TEST_CASE(cant_define_function_with_incorrect_name)
		{
			VerifyCommandHandling("fn 1XPLUSX", "Function cant be created\n");
			VerifyCommandHandling("fn", "Function cant be created\n");
			VerifyCommandHandling("fn @", "Function cant be created\n");
		}

		BOOST_AUTO_TEST_CASE(cant_define_function_with_nonexistent_variable_value)
		{
			VerifyCommandHandling("fn f1=ch1", "Function cant be created\n");
		}

		BOOST_AUTO_TEST_CASE(cant_define_function_with_nonexistent_variable_in_expression)
		{
			VerifyCommandHandling("fn f1=ch1+ch2", "Function cant be created\n");
		}

		BOOST_AUTO_TEST_CASE(can_define_correct_function)
		{
			ExecuteCommand("let ch1=10");
			ExecuteCommand("let ch2=5");
			ExecuteCommand("fn f=ch1");
			ExecuteCommand("fn f1=ch1*ch2");
			ExecuteCommand("fn f2=ch1-ch2");
			ExecuteCommand("fn f3=ch1+ch2");
			ExecuteCommand("fn f4=ch1/ch2");

			VerifyCommandHandling("print f1", "f1:50.00\n");
			VerifyCommandHandling("print f2", "f2:5.00\n");
			VerifyCommandHandling("print f3", "f3:15.00\n");
			VerifyCommandHandling("print f4", "f4:2.00\n");
		}

		BOOST_AUTO_TEST_CASE(cant_define_already_existent_function)
		{
			ExecuteCommand("let ch1=10");
			ExecuteCommand("fn f=ch1*ch1");
			VerifyCommandHandling("fn f=ch1", "Function cant be created\n");
		}
	BOOST_AUTO_TEST_SUITE_END();

	struct when_variables_and_functions_were_defined_ : CalculatorControlFixture
	{
		when_variables_and_functions_were_defined_()
		{
			calculator.AssignValueToVariable("x", "100");
			calculator.AssignValueToVariable("y", "45");
			calculator.AssignValueToVariable("z", "5");
			calculator.AddVariable("k");
			calculator.AddVariable("m");
			calculator.DefineFunction("f1","y", "x", Operation::ADDITION);
			calculator.DefineFunction("f2","y", "x", Operation::MULTIPLICATION);
			calculator.DefineFunction("f3","y", "x", Operation::SUBTRACTION);
			calculator.DefineFunction("f4","y", "x", Operation::DIVISION);
		}
	};

	BOOST_AUTO_TEST_SUITE(print_functions_test)
		BOOST_AUTO_TEST_CASE(cant_print_nonexistent_identifier)
		{
			VerifyCommandHandling("print ch1", "Unknown identifier\n");
			VerifyCommandHandling("print f1", "Unknown identifier\n");
		}

		BOOST_AUTO_TEST_CASE(cant_print_empty_variables_list)
		{
			VerifyCommandHandling("printvars", "No one variable was specified\n");
		}

		BOOST_AUTO_TEST_CASE(cant_print_empty_functions_list)
		{
			VerifyCommandHandling("printfns", "No one function was specified\n");
		}

		BOOST_FIXTURE_TEST_SUITE(print_functions_and_variables_test, when_variables_and_functions_were_defined_)			
			BOOST_AUTO_TEST_CASE(can_print_correct_identifier)
			{
				VerifyCommandHandling("print x", "x:100.00\n");
				VerifyCommandHandling("print k", "k:nan\n");
			}

			BOOST_AUTO_TEST_CASE(can_print_all_variables_when_they_were_defined)
			{
				VerifyCommandHandling("printvars", "k:nan\nm:nan\nx:100.00\ny:45.00\nz:5.00\n");
			}

			BOOST_AUTO_TEST_CASE(can_print_all_functions_when_they_were_defined)
			{
				VerifyCommandHandling("printfns", "f1:145.00\nf2:4500.00\nf3:-55.00\nf4:0.45\n");
			}
		BOOST_AUTO_TEST_SUITE_END();
	BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();

























