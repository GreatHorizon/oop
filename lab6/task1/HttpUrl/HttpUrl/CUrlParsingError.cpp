#include "stdafx.h"
#include "CUrlParsingError.h"


CUrlParsingError::CUrlParsingError(std::string const& message)
	: invalid_argument(message)
{
}
