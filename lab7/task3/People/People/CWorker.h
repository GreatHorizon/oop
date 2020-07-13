#pragma once
#include "CPersonImpl.h"
#include "IWorker.h"

class CWorker final : public CPersonImpl<IWorker> 
{
public:
	CWorker(std::string const& firstName, std::string const& lastName,
		std::string const& patronymic, std::string const& address,
		std::string const& specialisation);
	std::string GetSpecialisation() const override;
	void SetSpecialisation(std::string const& specialisation) override;
private:
	std::string m_specialisation;


};

