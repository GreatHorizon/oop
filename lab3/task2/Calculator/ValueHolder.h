#pragma once
#include <optional>
#include <map>
#include <string>

enum class Operation
{
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	NONE
};

class ValueHolder
{
public:
	virtual ~ValueHolder() = default;
	virtual std::optional<double> GetValue() const = 0;
	virtual void SetValue(double value) = 0;
	virtual bool GetState() const = 0;
	virtual std::string GetClassName() const = 0;
	virtual std::string GetLeftIdentifier() const = 0;
	virtual std::string GetRightIdentifier() const = 0;
	virtual Operation GetOperation() const = 0;
};

class Variable : public ValueHolder
{
public:
	void SetValue(double value);
	bool GetState() const;
	std::optional<double> GetValue() const;
	std::string GetClassName() const;
	std::string GetLeftIdentifier() const;
	std::string GetRightIdentifier() const;
	Operation GetOperation() const;
	Variable(double value = 0, bool state = false);
	
private:
	double m_value = 0;
	bool m_isInitialized = false;
	static const std::string CLASS_NAME;
};

class Function : public ValueHolder
{
public:
	void SetValue(double value);
	bool GetState() const;
	std::string GetClassName() const;
	std::string GetLeftIdentifier() const;
	std::string GetRightIdentifier() const;
	Operation GetOperation() const;
	std::optional<double> GetValue() const;
	Function(const std::string& lVariable, const std::string& rVariable = "",
		const Operation& operation = Operation::NONE);

private:
	std::string m_leftVariable;
	std::string m_rightVariable;
	Operation m_operation;
	double m_value = 0;
	bool m_isCalculated = false;
	static const std::string CLASS_NAME;
};


