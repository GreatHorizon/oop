#include "stdafx.h"
#include "CalculatorControl.h"
#include "Calculator.h"
#include "ValueHolder.h"

using namespace std;
using namespace std::placeholders;

const string CCalculatorControl::VARIABLE_CLASS_NAME = "Variable";
const string CCalculatorControl::FUNCTION_CLASS_NAME = "Function";

CCalculatorControl::CCalculatorControl(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap(
		{
			{"var", bind(&CCalculatorControl::DefineVariable, this, _1)},
			{"let", bind(&CCalculatorControl::AssignVariable, this, _1)},
			{"fn", bind(&CCalculatorControl::DefineFunction, this, _1)},
			{"print", bind(&CCalculatorControl::PrintIdentifier, this, _1)},
			{"printvars", bind(&CCalculatorControl::PrintVariables, this, _1)},
			{"printfns", bind(&CCalculatorControl::PrintFunctions, this, _1)},
		}
	)
{
}

bool CCalculatorControl::HandleCommand()
{
	string command;
	getline(m_input, command);
	istringstream stream(command);

	string action;
	stream >> action;
	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(stream);
	}

	return false;
}

bool CCalculatorControl::DefineVariable(std::istream& args)
{
	string identifier;
	getline(args, identifier);
	boost::trim_all(identifier);

	if (m_calculator.AddVariable(identifier))
	{
		return true;
	}
	m_output << "Variable cant be created\n";
	return true;
}

bool CCalculatorControl::DefineFunction(std::istream& args)
{
	string expression, functionName, lVariable, rVariable;
	Operation operation = Operation::NONE;
	getline(args, functionName, '=');
	boost::trim_all(functionName);
	getline(args, expression);

	if (m_calculator.DefineFunction(functionName, expression, rVariable, operation))
	{
		return true;
	}

	const vector<char> operations{ '+', '-', '/', '*' };
	auto result = std::find_first_of(expression.begin(), expression.end(),
	operations.begin(), operations.end());

	if (result == expression.end())
	{
		lVariable = expression;
	}
	else
	{
		lVariable = string(expression.begin(), result);
		rVariable = string(result + 1, expression.end());
		operation = ProcessOperation(*result);
	}

	if (!m_calculator.DefineFunction(functionName, lVariable, rVariable, operation))
	{
		m_output << "Function cant be created\n";
	}

	return true;	
}

Operation CCalculatorControl::ProcessOperation(char operationSymbol)
{
	if (operationSymbol == '+')
	{
		return Operation::ADDITION;
	}

	if (operationSymbol == '-')
	{
		return Operation::SUBTRACTION;
	}

	if (operationSymbol == '/')
	{
		return Operation::DIVISION;
	}

	return Operation::MULTIPLICATION;
}

bool CCalculatorControl::AssignVariable(std::istream& args)
{
	std::string rValue, lIdentifier;
	getline(args, lIdentifier, '=');
	boost::trim_all(lIdentifier);
	getline(args, rValue);

	if (!m_calculator.AssignValueToVariable(lIdentifier, rValue))
	{
		m_output << "Variable cant be assigned\n";
		return true;
	}

	m_calculator.UpdateFunctionValue(lIdentifier);
	return true;
}

bool CCalculatorControl::PrintIdentifier(std::istream& args)
{
	string identifierName;
	getline(args, identifierName);
	boost::trim_all(identifierName);

	auto valueMap = m_calculator.GetValueMap();
	if (auto identifier = valueMap.find(identifierName);
		identifier != valueMap.end())
	{
		m_output << identifierName << ":";
		identifier->second->GetValue() ? m_output << std::fixed << setprecision(2)
			<< identifier->second->GetValue().value() << "\n"
			: m_output << "nan\n";
	}
	else
	{
		m_output << "Unknown identifier\n";
	}

	return true;
}

bool CCalculatorControl::PrintVariables(std::istream& args)
{
	auto valueMap = m_calculator.GetValueMap();

	if (valueMap.empty())
	{
		m_output << "No one variable was specified\n";
		return true;
	}

	for (auto identifier : valueMap)
	{
		if (identifier.second->GetClassName() == VARIABLE_CLASS_NAME)
		{
			m_output << identifier.first << ":";
			identifier.second->GetValue() ? m_output << std::fixed << setprecision(2) 
				<< identifier.second->GetValue().value() << "\n"
				: m_output << "nan\n";
		}
	}

	return true;
}

bool CCalculatorControl::PrintFunctions(std::istream& args)
{
	auto valueMap = m_calculator.GetValueMap();

	if (valueMap.empty())
	{
		m_output << "No one function was specified\n";
		return true;
	}

	for (auto identifier : valueMap)
	{
		if (identifier.second->GetClassName() == FUNCTION_CLASS_NAME)
		{
			m_output << identifier.first << ":";
			identifier.second->GetValue() ? m_output << std::fixed << setprecision(2)
				<< identifier.second->GetValue().value() << "\n"
				: m_output << "nan\n";
		}
	}

	return true;
}