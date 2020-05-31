#include "stdafx.h"
#include "CHttpUrl.h"
#include <regex>

Protocol GetParsedProtocol(std::string protocolName)
{
    std::transform(protocolName.begin(), protocolName.end(), protocolName.begin(), tolower);

    if (protocolName == "http")
    {
        return Protocol::HTTP;
    }

    if (protocolName == "https")
    {
        return Protocol::HTTPS;
    }

    throw CUrlParsingError("Invalid protocol\nIt should be http or https\n");
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	auto match = ParseUrl(url);

    m_protocol = GetParsedProtocol(match[1]);
    m_domain = CheckDomain(match[2]);
    m_port = GetParsedPort(match[4], m_protocol);
    m_document = match[6];
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
    m_domain = CheckDomain(domain);
    m_protocol = protocol;
    m_port = GetDefaultPort(protocol);
    m_document = SupplementDocument(document);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
    m_domain = CheckDomain(domain);
    m_protocol = protocol;
    m_document = SupplementDocument(document);
    m_port = port;
}

std::string CHttpUrl::SupplementDocument(std::string const& document)
{
    if (document.empty() || document[0] != '/')
    {
        return '/' + document;
    }

    return document;
}

std::string CHttpUrl::CheckDomain(std::string const& domain)
{
    if (domain.empty())
    {
        throw CUrlParsingError("Domain should not be empty\n");
    }

    for (auto symbol: domain)
    {
        if (!isascii(symbol) || 
            (!isalpha(symbol) && !isdigit(symbol) && symbol != '-' && symbol != '.'))
        {
            throw CUrlParsingError("Domain should contain only a-z, A-Z, 0-9, \'.\', \'-\'\n");
        }
    }

    return domain;
}

std::string CHttpUrl::GetURL() const
{
    std::string url;
    m_protocol == Protocol::HTTP ? url += "http://" : url += "https://";
    url += m_domain;

    if (m_port != GetDefaultPort(m_protocol))
    {
        url += ":" + std::to_string(m_port);
    }

    url += m_document;
    return url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::smatch CHttpUrl::ParseUrl(std::string const& url)
{
	std::smatch match;
	std::regex reg("^(\\w+)://([^:\\s/]+)(:(\\d+))?(/(\\S+)?)?$");

	if (!regex_search(url, match, reg))
	{
		throw CUrlParsingError("Invalid url\n");
	}

    return match;
}

unsigned short CHttpUrl::GetParsedPort(std::string const& portLine, Protocol const& protocol)
{
    int port;
    size_t errorPosition;

    if (!portLine.empty())
    {
        try
        {
            port = stoi(portLine, &errorPosition, 10);

            if (port < 1 || port > 65535)
            {
                throw std::exception();
            }
        }
        catch (const std::exception&)
        {
            throw CUrlParsingError("Invalid port\nIt should be number from 1 to 65535\n");
        }

        return port;
    }

    return GetDefaultPort(protocol);    
}

unsigned short CHttpUrl::GetDefaultPort(Protocol const& protocol)
{    
    return DEFAULT_PORT.find(protocol)->second;
}


