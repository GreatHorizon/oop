#pragma once
#include <stdexcept>
#include <exception>

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(std::string const& message);
};

