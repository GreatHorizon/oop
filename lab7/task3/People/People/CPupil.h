#pragma once
#include "CPersonImpl.h"
#include "IPupil.h"

class CPupil final : public CPersonImpl<IPupil>
{
public:
	CPupil(std::string const& firstName, std::string const& lastName,
		std::string const& patronymic, std::string const& address,
		std::string const& schoolName, std::string const& className);

	std::string GetSchoolName() const override;
	std::string GetClassName() const override;

	void SetClassName(std::string const& className) override;
	void SetSchoolName(std::string const& schoolName) override;
private:
	std::string m_schoolName;
	std::string m_className;
};

