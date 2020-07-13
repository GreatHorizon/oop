#include "CStudent.h"

CStudent::CStudent(std::string const& firstName, std::string const& lastName,
	std::string const& patronymic, std::string const& address, std::string const& studentId,
	std::string const& universityName)
	: CStudentImpl(firstName, lastName, patronymic, address, studentId, universityName)
{
}
