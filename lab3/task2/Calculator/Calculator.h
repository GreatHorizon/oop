#pragma once

#include <optional>
#include <map>
#include <string>
class ValueHolder;
enum class Operation;

class CCalculator 
{
public:
	bool AddVariable(const std::string& identifier, double value=0, bool isInitialized=false);
	bool AssignValueToVariable(const std::string& lIdentifier, const std::string& rValue);
	bool DefineFunction(const std::string& functionName,
		const std::string& lIdentifier, const std::string& rIdentifier, Operation operation);
	bool DefineFunction(const std::string& functionName, const std::string& lIdentifier);
	std::map<std::string, ValueHolder*> GetValueMap() const;
	void UpdateFunctionValue(const std::string& identifier);
	~CCalculator();

private:
	std::map<std::string, ValueHolder*> m_valueMap;
	bool IsCorrectIdentifier(const std::string& identifier) const;
	std::optional<double> ConvertDigitStringIntoNumber(const std::string& valueLine) const;
	bool DoesNameAlreadyTaken(const std::string& identifier); 
	std::optional<double> CalculateValue(const std::string& lIdentifier,
		const std::string& rIdentifier, Operation operation);
	std::optional<double> CalculateValue(const std::string& lIdentifier);
	static const std::string FUNCTION_CLASS_NAME;
	
};

