#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"


int main()
{
	std::string url;

	while (std::getline(std::cin, url))
	{
		try
		{
			CHttpUrl parsedUrl(url);
		}
		catch (CUrlParsingError const& exeption)
		{
			std::cout << exeption.what();
		}
	}	
}