#include "stdafx.h"
#include "Calculator.h"
#include "ValueHolder.h"

using namespace std;
using namespace std::placeholders;

CCalculator::~CCalculator()
{
	for (auto identifier : m_valueMap)
	{
		delete[] identifier.second;
	}
}

bool CCalculator::AddVariable(const std::string& identifier, double value, bool isInitialized)
{
	if (!DoesNameAlreadyTaken(identifier) && IsCorrectIdentifier(identifier))
	{
		ValueHolder* variable = new Variable(value, isInitialized);
		m_valueMap.emplace(identifier, variable);
		return true;
	}

	return false;
}

bool CCalculator::AssignValueToVariable(const std::string& lIdentifier, const std::string& rValue)
{
	if (!DoesNameAlreadyTaken(lIdentifier) && !IsCorrectIdentifier(lIdentifier))
	{
		return false;
	}

	double assignedValue;
	auto lVariable = m_valueMap.find(lIdentifier);
	if (lVariable != m_valueMap.end() && lVariable->second->GetClassName() == "Function")
	{
		return false;
	}

	if (auto value = ConvertDigitStringIntoNumber(rValue); 
		value)
	{
		assignedValue = value.value();
	}
	else
	{
		auto rVariable = m_valueMap.find(rValue);
		if (rVariable != m_valueMap.end() && rVariable->second->GetValue())
		{
			assignedValue = rVariable->second->GetValue().value();
		}
		else
		{
			return false;
		}
	}

	if (lVariable != m_valueMap.end())
	{
		lVariable->second->SetValue(assignedValue);
	}
	else if (IsCorrectIdentifier(lIdentifier))
	{
		AddVariable(lIdentifier, assignedValue, true);
	}

	return true;
}

bool CCalculator::DefineFunction(const std::string& functionName, 
	const std::string& lIdentifier, const std::string& rIdentifier, Operation operation)
{
	if (DoesNameAlreadyTaken(functionName) || !IsCorrectIdentifier(functionName))
	{
		return false;
	}

	if (!rIdentifier.empty())
	{
		auto rVariable = m_valueMap.find(rIdentifier);
		auto lVariable = m_valueMap.find(lIdentifier);

		if (lVariable != m_valueMap.end() && rVariable != m_valueMap.end())
		{
			auto value = CalculateValue(lIdentifier, rIdentifier, operation);
			ValueHolder* function = new Function(lIdentifier, rIdentifier, operation);
			if (value)
			{
				function->SetValue(value.value());
			}
			m_valueMap.emplace(functionName, function);
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool CCalculator::DefineFunction(const std::string& functionName, const std::string& lIdentifier)
{
	if (DoesNameAlreadyTaken(functionName) || !IsCorrectIdentifier(functionName))
	{
		return false;
	}

	if (auto value = m_valueMap.find(lIdentifier);
		value != m_valueMap.end())
	{
		ValueHolder* function = new Function(lIdentifier);
		if (auto oValue = CalculateValue(lIdentifier);
			oValue)
		{
			function->SetValue(oValue.value());
		}
		m_valueMap.emplace(functionName, function);
		return true;
	}

	return false;
}

std::optional<double> CCalculator::CalculateValue(const std::string& lIdentifier,
	const std::string& rIdentifier, Operation operation)
{
	auto lVariable = m_valueMap.find(lIdentifier);
	auto rVariable = m_valueMap.find(rIdentifier);

	if (rVariable->second->GetState() && lVariable->second->GetState())
	{
		double rValue = rVariable->second->GetValue().value();
		double lValue = lVariable->second->GetValue().value();
		switch (operation)
		{
		case Operation::ADDITION:
			return lValue + rValue;
		case Operation::SUBTRACTION:
			return lValue - rValue;
		case Operation::MULTIPLICATION:
			return lValue * rValue;
		case Operation::DIVISION:
			return lValue / rValue;
		}
	}
	return std::nullopt;
}


std::optional<double> CCalculator::CalculateValue(const std::string& lIdentifier)
{
	auto lVariable = m_valueMap.find(lIdentifier);
	if (lVariable->second->GetState())
	{
		return lVariable->second->GetValue();
	}
	return std::nullopt;
}

std::map<std::string, ValueHolder*> CCalculator::GetValueMap() const
{
	return m_valueMap;
}

void CCalculator::UpdateFunctionValue(const std::string& identifier)
{
	for (auto value : m_valueMap)
	{
		if (value.second->GetClassName() == "Function" &&
			(value.second->GetLeftIdentifier() == identifier ||
				value.second->GetRightIdentifier() == identifier))
		{
			optional<double> currentValue = value.second->GetValue();
			optional<double> updatedValue;

			updatedValue = value.second->GetRightIdentifier().empty() 
				? updatedValue = CalculateValue(value.second->GetLeftIdentifier())
				: CalculateValue(value.second->GetLeftIdentifier(),
					value.second->GetRightIdentifier(), value.second->GetOperation());

			if (!currentValue && updatedValue)
			{
				value.second->SetValue(updatedValue.value());
				UpdateFunctionValue(value.first);
			}
			
			if ((currentValue && updatedValue) && (currentValue.value() != updatedValue.value()))
			{
				value.second->SetValue(updatedValue.value());
				UpdateFunctionValue(value.first);
			}
		}
	}
}

bool CCalculator::DoesNameAlreadyTaken(const std::string& identifier)
{
	return m_valueMap.find(identifier) == m_valueMap.end() ? false : true;
}

bool CCalculator::IsCorrectIdentifier(const std::string& identifier) const
{
	if (identifier.empty())
	{
		return false;
	}

	for (auto symbol : identifier)
	{
		if (!(isascii(symbol)))
		{
			return false;
		}

		if (!(isalpha(symbol)) && !(isdigit(symbol)) && (symbol != '_'))
		{
			return false;
		}
	}

	if (isdigit(identifier[0]))
	{
		return false;
	}

	return true;
}

std::optional<double> CCalculator::
ConvertDigitStringIntoNumber(const std::string& valueLine) const
{
	double number = 0;
	size_t stoppedAt;
	try
	{
		number = stod(valueLine, &stoppedAt);
	}
	catch (const std::exception&)
	{
		return std::nullopt;
	}

	if (valueLine[stoppedAt] != '\0')
	{
		return std::nullopt;
	}

	return number;
}