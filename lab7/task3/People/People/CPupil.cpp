#include "CPupil.h"

CPupil::CPupil(std::string const& firstName, std::string const& lastName, 
	std::string const& patronymic, std::string const& address, 
	std::string const& schoolName, std::string const& className)
	: m_schoolName(schoolName)
	, m_className(className)
	, CPersonImpl(firstName, lastName, patronymic, address)
{
}

std::string CPupil::GetSchoolName() const
{
	return m_schoolName;
}

std::string CPupil::GetClassName() const
{
	return m_className;
}

void CPupil::SetClassName(std::string const& className)
{	
	m_className = className;
}

void CPupil::SetSchoolName(std::string const& schoolName)
{
	m_schoolName = schoolName;
}
