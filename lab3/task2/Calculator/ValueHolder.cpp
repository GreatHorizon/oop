#include "stdafx.h"
#include "ValueHolder.h"
const std::string Variable::CLASS_NAME = "Variable";
const std::string Function::CLASS_NAME = "Function";


Variable::Variable(double value, bool state) 
	: m_value(value)
	, m_isInitialized(state)
{
}

void Variable::SetValue(double value)
{
	m_value = value;
	m_isInitialized = true;
}

void Function::SetValue(double value)
{
	m_value = value;
	m_isCalculated = true;
}

bool Variable::GetState() const
{
	return m_isInitialized;
}

std::optional<double> Function::GetValue() const
{	
	if (m_isCalculated)
	{
		return m_value;
	}
	return std::nullopt;
}

std::optional<double> Variable::GetValue() const
{
	if (m_isInitialized)
	{
		return m_value;
	}

	return std::nullopt;
}

Function::Function(const std::string& lVariable, const std::string& rVariable,
	const Operation& operation)
	: m_leftVariable(lVariable)
	, m_rightVariable(rVariable)
	, m_operation(operation)
{
}

bool Function::GetState() const
{
	return m_isCalculated;
}

std::string Function::GetClassName() const
{
	return CLASS_NAME;
}

std::string Function::GetLeftIdentifier() const
{
	return m_leftVariable;
}

std::string Function::GetRightIdentifier() const
{
	return m_rightVariable;
}

Operation Function::GetOperation() const
{
	return m_operation;
}

std::string Variable::GetClassName() const
{
	return CLASS_NAME;
}

std::string Variable::GetLeftIdentifier() const
{
	return std::string();
}

std::string Variable::GetRightIdentifier() const
{
	return std::string();
}

Operation Variable::GetOperation() const
{
	return Operation::NONE;
}