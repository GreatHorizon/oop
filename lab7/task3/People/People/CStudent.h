#pragma once
#include "CStudentImpl.h"
#include "IStudent.h"

class CStudent final : public CStudentImpl<IStudent>
{
public:
	CStudent(std::string const& firstName, std::string const& lastName,
		std::string const& patronymic, std::string const& address, std::string const& studentId,
		std::string const& universityName);
};

