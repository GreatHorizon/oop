#pragma once
#include <optional>

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

const int LOWER_LIMIT = 1;
const int UPPER_LIMIT = 65535;
const std::string NOT_SPECIFIED = "was not specified";

bool ParseURL(std::string const& url, Protocol& protocol, int& port,
    std::string& host, std::string& document);

void PrintURLInfo(std::string const& url, Protocol& protocol, int& port,
    std::string& host, std::string& document);

void ProcessUsersInput();

std::optional<Protocol> GetProtocol(std::string protocolName);

std::optional<int> GetPort(const std::string& portLine, const Protocol& protocol);
