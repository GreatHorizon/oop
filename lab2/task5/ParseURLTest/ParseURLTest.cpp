#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "..\\ParseURL\ParseURL.h"

using namespace std;

SCENARIO("Test GetProtocol()")
{
	WHEN("protocol incorrect")
	{
		THEN("should return nullopt")
		{
			CHECK(nullopt == GetProtocol("Hpp"));
			CHECK(nullopt == GetProtocol("fhp"));
		}
	}

	WHEN("protocol in lower case correct")
	{
		THEN("should return enum protocol")
		{
			CHECK(Protocol::HTTP == GetProtocol("http"));
			CHECK(Protocol::FTP == GetProtocol("ftp"));
			CHECK(Protocol::HTTPS == GetProtocol("https"));
		}
	}

	WHEN("protocol in upper case correct")
	{
		THEN("should return enum protocol")
		{
			CHECK(Protocol::HTTP == GetProtocol("HTTP"));
			CHECK(Protocol::FTP == GetProtocol("ftp"));
			CHECK(Protocol::HTTPS == GetProtocol("HTTPS"));
		}
	}
}

SCENARIO("Test GetPort()")
{
	WHEN("port was not specified")
	{
		WHEN("protocol is http")
		{
			THEN("should return port = 80")
			{
				CHECK(80 == GetPort("", Protocol::HTTP).value());
			}
		}

		WHEN("protocol is ftp")
		{
			THEN("should return port = 21")
			{
				CHECK(21 == GetPort("", Protocol::FTP).value());
			}
		}

		WHEN("protocol is https")
		{
			THEN("should return port = 443")
			{
				CHECK(443 == GetPort("", Protocol::HTTPS).value());
			}
		}
	}

	WHEN("port was specified")
	{
		WHEN("port is correct")
		{
			THEN("should return integer value of 221 string value")
			{
				CHECK(221 == GetPort("221", Protocol::HTTPS).value());
			}
		}

		WHEN("port is out of 1 - 65535")
		{
			THEN("should return nullopt")
			{
				CHECK(nullopt == GetPort("99999999", Protocol::HTTPS));
				CHECK(nullopt == GetPort("0", Protocol::HTTPS));
			}
		}

		WHEN("port is non digit value")
		{
			THEN("should return nullopt")
			{
				CHECK(nullopt == GetPort("asdas", Protocol::HTTPS));
			}
		}
	}
}

SCENARIO("Test ParseURL()")
{
	string host;
	string document;
	int port; 
	Protocol protocol;
	
	WHEN("empty url")
	{
		THEN("should return false")
		{
			CHECK(false == ParseURL("", protocol, port, host, document));
		}
	}

	WHEN("incorrect url")
	{
		WHEN("incorrect protocol")
		{
			THEN("should return false")
			{
				CHECK(false == ParseURL("vk.com", protocol, port, host, document));
				CHECK(false == ParseURL("htp://vk.com", protocol, port, host, document));
			}
		}

		WHEN("host is empty")
		{
			THEN("should return false")
			{
				CHECK(false == ParseURL("http://", protocol, port, host, document));
			}
		}

		WHEN("port out of 1 - 65535")
		{
			THEN("should return false")
			{
				CHECK(false == ParseURL("http://github.com:999999999", protocol, port, host, document));
			}
		}

		WHEN("empty port")
		{
			THEN("should return false")
			{
				CHECK(false == ParseURL("https://vk.com:", protocol, port, host, document));
			}
		}
	}

	WHEN("correct url")
	{
		WHEN("specified only protocol and host")
		{
			THEN("should return protocol, default port, host and document")
			{
				CHECK(true == ParseURL("http://vk.com", protocol, port, host, document));
				CHECK(Protocol::HTTP == protocol);
				CHECK("vk.com" == host);
				CHECK(80 == port);
				CHECK(NOT_SPECIFIED == document);
			}
		}

		WHEN("specified protocol, host and port")
		{
			THEN("should return protocol, port, host and empty document")
			{
				CHECK(true == ParseURL("https://vk.com:123", protocol, port, host, document));
				CHECK(Protocol::HTTPS == protocol);
				CHECK("vk.com" == host);
				CHECK(123 == port);
				CHECK(NOT_SPECIFIED == document);
			}
		}

		WHEN("specified protocol, host, port and document")
		{
			THEN("should return protocol, port, host and document")
			{
				CHECK(true == ParseURL("https://vk.com:600/news/234", protocol, port, host, document));
				CHECK(Protocol::HTTPS == protocol);
				CHECK("vk.com" == host);
				CHECK(600 == port);
				CHECK("news/234" == document);
			}
		}

		WHEN("specified protocol, host, port and empty document")
		{
			THEN("should return protocol, port, host and empty document")
			{
				CHECK(true == ParseURL("https://vk.com:600/", protocol, port, host, document));
				CHECK(Protocol::HTTPS == protocol);
				CHECK("vk.com" == host);
				CHECK(600 == port);
				CHECK(NOT_SPECIFIED == document);
			}
		}	
	}

}

