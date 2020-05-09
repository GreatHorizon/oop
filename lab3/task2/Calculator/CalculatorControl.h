#pragma once
#include <boost/noncopyable.hpp>
enum class Operation;
class CCalculator;
class ValueHolder; 

class CCalculatorControl : boost::noncopyable
{
public:

	CCalculatorControl(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();
private:
	typedef std::function<bool(std::istream& args)> Handler;
	typedef std::map<std::string, Handler> ActionMap;

	bool DefineVariable(std::istream& args);
	bool AssignVariable(std::istream& args);
	bool DefineFunction(std::istream& args); 
	bool PrintIdentifier(std::istream& args);
	Operation ProcessOperation(char operationSymbol);
	bool PrintVariables(std::istream& args);
	bool PrintFunctions(std::istream& args);

private:
	std::istream& m_input;
	std::ostream& m_output;
	ActionMap m_actionMap;
	CCalculator& m_calculator;
	static const std::string VARIABLE_CLASS_NAME;
	static const std::string FUNCTION_CLASS_NAME;

};

