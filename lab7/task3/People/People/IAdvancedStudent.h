#pragma once
#include "IStudent.h"
class IAdvancedStudent : public IStudent 
{
public:

	virtual std::string GetDissertationSubject() const = 0;
	virtual void SetDissertationSubject(std::string const& dissertationSubject) = 0;
};

