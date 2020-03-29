#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "..\HTMLDecode\implementation.h"
using namespace std;

TEST_CASE("empty string should be converted to empty string")
{
	string required;
	string outputString;
	string inputString;

	inputString = "";
	outputString = HtmlDecode(inputString);
	required = "";
	CHECK(outputString == required);
}

TEST_CASE("string without entities should not changed")
{
	string required;
	string outputString;
	string inputString;

	inputString = "who is there?";
	outputString = HtmlDecode(inputString);
	required = "who is there?";
	CHECK(outputString == required);
}

TEST_CASE("should replace ampersand")
{
	string required;
	string outputString;
	string inputString;

	inputString = "DDD&amp;FFF";
	outputString = HtmlDecode(inputString);
	required = "DDD&FFF";
	CHECK(outputString == required);
}

TEST_CASE("should replace ampersand and quotes")
{
	string required;
	string outputString;
	string inputString;

	inputString = "&quot;&amp;&quot;";
	outputString = HtmlDecode(inputString);
	required = "\"&\"";
	CHECK(outputString == required);
}

TEST_CASE("should replace quotes, ampersand, brackets")
{
	string required;
	string outputString;
	string inputString;

	inputString = "&lt;A&lt;B&quot;&amp;&quot;C&gt;D&gt;";
	outputString = HtmlDecode(inputString);
	required = "<A<B\"&\"C>D>";
	CHECK(outputString == required);
}
	
