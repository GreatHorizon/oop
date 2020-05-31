#pragma once
#include "CUrlParsingError.h"
#include <string>
#include <map>
#include <regex>

enum class Protocol
{
	HTTP,
	HTTPS
};

const std::map<Protocol, unsigned short> DEFAULT_PORT =
{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443}
};

class CHttpUrl
{
public:

	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	static std::smatch ParseUrl(std::string const& url);
	static unsigned short GetParsedPort(std::string const& portLine, Protocol const& protocol);
	static unsigned short GetDefaultPort(Protocol const& protocol);
	static std::string CheckDomain(std::string const& domain);
	static std::string SupplementDocument(std::string const& document);

private:
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
};


