#pragma once
#include "IPerson.h"

class IWorker : public IPerson
{
public:
	virtual std::string GetSpecialisation() const = 0;
	virtual void SetSpecialisation(std::string const& specialisation) = 0;
};

