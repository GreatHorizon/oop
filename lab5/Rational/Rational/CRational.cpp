#include "CRational.h"
#include "stdafx.h"

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

int GetGCD(int firstNumber, int secondNumber)
{
	int t;
	while (secondNumber != 0)
	{
		t = secondNumber;
		secondNumber = firstNumber % secondNumber;
		firstNumber = t;
	}

	return firstNumber;
}

std::pair<int, int> GetNormalizedValues(int numerator, int denominator)
{
	int sign = 1;
	if (denominator == 0)
	{
		return std::make_pair(0, 1);
	}

	if (denominator < 0)
	{
		sign = -1;
	}

	auto gcd = abs(GetGCD(numerator, denominator));

	return gcd == 1 ? std::make_pair(numerator * sign, denominator * sign) :
		std::make_pair(numerator * sign / gcd, denominator / gcd * sign);
}

CRational::CRational(int numerator, int denominator)
{
	auto values = GetNormalizedValues(numerator, denominator);
	m_numerator = values.first;
	m_denominator = values.second;
}


int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return m_numerator / static_cast<double>(m_denominator);
}

CRational const CRational::operator +() const
{
	return *this;
}

CRational const CRational::operator -() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator +=(const CRational& rightValue)
{
	*this = *this + rightValue;
	return *this;
}

CRational& CRational::operator -=(const CRational& rightValue)
{
	*this = *this - rightValue;
	return *this;
}

CRational& CRational::operator *=(const CRational& rightValue)
{
	*this = *this * rightValue;
	return *this;
}

CRational& CRational::operator /=(const CRational& rightValue)
{
	*this = *this / rightValue;
	return *this;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integralPart = GetNumerator() / GetDenominator();
	auto number = CRational(GetNumerator() - integralPart, GetDenominator());

	return std::make_pair(integralPart, number);
}

bool operator ==(const CRational& leftValue, const CRational& rightValue)
{
	return (leftValue.GetNumerator() == rightValue.GetNumerator() 
		&& leftValue.GetDenominator() == rightValue.GetDenominator());
}

bool operator !=(const CRational& leftValue, const CRational& rightValue)
{
	return !(leftValue == rightValue);
}

bool operator >(const CRational& leftValue, const CRational& rightValue)
{
	return (leftValue.GetNumerator() * rightValue.GetDenominator() 
	> leftValue.GetDenominator() * rightValue.GetNumerator());
}

bool operator <(const CRational& leftValue, const CRational& rightValue)
{
	return (leftValue.GetNumerator() * rightValue.GetDenominator()
	< leftValue.GetDenominator() * rightValue.GetNumerator());
}

bool operator >=(const CRational& leftValue, const CRational& rightValue)
{
	return (leftValue > rightValue) || (leftValue == rightValue);
}

bool operator <=(const CRational& leftValue, const CRational& rightValue)
{
	return (leftValue < rightValue) || (leftValue == rightValue);
}

CRational operator +(const CRational& leftValue, const CRational& rightValue)
{
	return CRational(leftValue.GetNumerator() * rightValue.GetDenominator() 
		+ rightValue.GetNumerator() * leftValue.GetDenominator(), 
		leftValue.GetDenominator() * rightValue.GetDenominator());
}

CRational operator -(const CRational& leftValue, const CRational& rightValue)
{
	return CRational(leftValue.GetNumerator() * rightValue.GetDenominator()
		- rightValue.GetNumerator() * leftValue.GetDenominator(),
		leftValue.GetDenominator() * rightValue.GetDenominator());
}

CRational operator *(const CRational& leftValue, const CRational& rightValue)
{
	return CRational(leftValue.GetNumerator() * rightValue.GetNumerator(),
		leftValue.GetDenominator() * rightValue.GetDenominator());
}

CRational operator /(const CRational& leftValue, const CRational& rightValue)
{	
	return CRational(leftValue.GetNumerator() * rightValue.GetDenominator(),
		leftValue.GetDenominator() * rightValue.GetNumerator());
}

std::optional<int> ConvertDigitStringIntoNumber(const std::string& valueLine)
{
	int number = 0;
	size_t stoppedAt;

	try
	{
		number = stoi(valueLine, &stoppedAt);
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

std::istream& operator >>(std::istream& stream, CRational& number)
{ 
	std::string numeratorString, denominatorString;
	getline(stream, numeratorString, '/');
	getline(stream, denominatorString);

	auto numerator = ConvertDigitStringIntoNumber(numeratorString);
	auto denominator = ConvertDigitStringIntoNumber(denominatorString);

	if (!numerator || !denominator)
	{
		std::cout <<  "Incorrect value\n";
		return stream;
	}

	number = CRational(numerator.value(), denominator.value());
	return stream;
}

std::ostream& operator <<(std::ostream& stream, const CRational& number)
{
	stream << number.GetNumerator() << "/" << number.GetDenominator() << "\n";
	return stream;
}

