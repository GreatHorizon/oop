#pragma once
#include "iostream"

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;

	double ToDouble() const;

	CRational const operator + () const;
	CRational const operator - () const;

	CRational& operator +=(const CRational& rightValue);
	CRational& operator -=(const CRational& rightValue);
	CRational& operator *=(const CRational& rightValue);
	CRational& operator /=(const CRational& rightValue);

	std::pair<int, CRational> ToCompoundFraction() const;

private:
	int m_numerator;
	int m_denominator;
};

CRational operator + (const CRational& leftValue, const CRational& rightValue);
CRational operator - (const CRational& leftValue, const CRational& rightValue);
CRational operator * (const CRational& leftValue, const CRational& rightValue);
CRational operator / (const CRational& leftValue, const CRational& rightValue);

bool operator ==(const CRational& leftValue, const CRational& rightValue);
bool operator !=(const CRational& leftValue, const CRational& rightValue);
bool operator >(const CRational& leftValue, const CRational& rightValue);
bool operator >=(const CRational& leftValue, const CRational& rightValue);
bool operator <(const CRational& leftValue, const CRational& rightValue);
bool operator <=(const CRational& leftValue, const CRational& rightValue);

std::istream& operator >> (std::istream& stream, CRational& number);
std::ostream& operator << (std::ostream& stream, const CRational& number);