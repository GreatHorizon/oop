#include "CWorker.h"

CWorker::CWorker(std::string const& firstName, std::string const& lastName, 
	std::string const& patronymic, std::string const& address, std::string const& specialisation)
	: m_specialisation(specialisation)
	, CPersonImpl(firstName, lastName, patronymic, address)
{
}

std::string CWorker::GetSpecialisation() const
{
	return m_specialisation;
}

void CWorker::SetSpecialisation(std::string const& specialisation)
{
	m_specialisation = specialisation;
}
