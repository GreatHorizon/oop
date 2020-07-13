#include "CAdvancedStudent.h"

std::string CAdvancedStudent::GetDissertationSubject() const
{
	return m_dissertationSubject;
}

void CAdvancedStudent::SetDissertationSubject(std::string const& dissertationSubject)
{
	m_dissertationSubject = dissertationSubject;
}

CAdvancedStudent::CAdvancedStudent(std::string const& firstName, std::string const& lastName, 
	std::string const& patronymic, std::string const& address, std::string const& studentId, 
	std::string const& universityName, std::string dissertationSubject)
	: m_dissertationSubject(dissertationSubject)
	, CStudentImpl(firstName, lastName, patronymic, address, studentId, universityName)
{
}

