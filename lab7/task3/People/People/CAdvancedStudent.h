#pragma once
#include "CStudentImpl.h"
#include "IAdvancedStudent.h"

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{
public:
	std::string GetDissertationSubject() const override; 
	void SetDissertationSubject(std::string const& dissertationSubject) override;
	CAdvancedStudent(std::string const& firstName, std::string const& lastName,
		std::string const& patronymic, std::string const& address, std::string const& studentId,
		std::string const& universityName, std::string dissertationSubject);
private:
	std::string m_dissertationSubject;
};

