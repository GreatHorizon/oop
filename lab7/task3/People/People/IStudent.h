#pragma once

#include "CPersonImpl.h"

class IStudent : public IPerson
{
public:
	virtual std::string GetUniversityName() const = 0;
	virtual std::string GetStudentId() const = 0;
	virtual void SetUniversityName(std::string const& universityName) = 0;
	virtual void SetStudentId(std::string const& studentId) = 0;
};

