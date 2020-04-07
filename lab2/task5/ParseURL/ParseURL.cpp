#include "stdafx.h"
#include "ParseURL.h"

using namespace std;

optional<Protocol> GetProtocol(string protocolName)
{
    transform(protocolName.begin(), protocolName.end(), protocolName.begin(), tolower);

    if (protocolName == "http")
    {
        return Protocol::HTTP;
    }

    if (protocolName == "ftp")
    {
        return Protocol::FTP;
    }

    if (protocolName == "https")
    {
        return Protocol::HTTPS;
    }

    return nullopt;
}

optional<int> GetPort(const string& portLine, const Protocol& protocol)
{
    int port;
    size_t* errorPosition = new size_t;
    if (!portLine.empty())
    {
        try
        {
            port = stoi(portLine, errorPosition, 10);
        }
        catch (exception)
        {
            return nullopt;
        }

        if (port < LOWER_LIMIT || port > UPPER_LIMIT)
        {
            return nullopt;
        }
        else
        {
            return port;
        }
    }
    auto defaultPort = DEFAULT_VALUES.find(protocol);
    return defaultPort->second;
}

bool ParseURL(string const& url, Protocol& protocol, int& port,
    string& host, string& document)
{
    smatch match;
    regex reg("^(\\w+)://([^:\\s/]+)(:(\\d+))?(/(\\S+)?)?$");

    if (!regex_search(url, match, reg))
    {
        return false;
    }

    optional optProtocol = GetProtocol(match[1]);
    if (!optProtocol)
    {
        cout << "Incorrect protocol" << "\n";
        cout << "It could be http, ftp, https" << "\n";
        return false;
    }

    optional optPort = GetPort(match[4], optProtocol.value());
    if (!optPort)
    {
        cout << "Incorrect port" << "\n";
        cout << "Port should be from 1 to 65535" << "\n";
        return false;
    }

    protocol = optProtocol.value();
    port = optPort.value();
    host = match[2];
    document = match[6];

    if (document.empty())
    {
        document = NOT_SPECIFIED;
    }

    return true;
}

void PrintURLInfo(string const& url, Protocol& protocol, int& port,
    string& host, string& document)
{
    cout << "HOST: " << host << "\n";
    cout << "PORT: " << port << "\n";
    cout << "DOC: " << document << "\n";
}

void ProcessUsersInput()
{
    int port;
    string url;
    string host;
    string document;
    Protocol protocol;

    cout << "Enter URL or ctrl+z to end program" << "\n";
    while (getline(cin, url))
    {
        if (ParseURL(url, protocol, port, host, document))
        {
            PrintURLInfo(url, protocol, port, host, document);
        }
        else
        {
            cout << "Icorrect data" << "\n";
            cout << "URL can not be parsed" << "\n";
        }

        cout <<"\n"<< "Enter URL or ctrl+z to end program" << "\n";
    }
}



