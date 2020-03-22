#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "..\HTMLDecode\implementation.h"
using namespace std;

TEST_CASE("Test HtmlDecode()")
{
	string required;
	string outputString;
	string inputString;

	//Пустая строка
	inputString = "";
	outputString = HtmlDecode(inputString);
	required = "";
	CHECK(outputString == required);

	//Строка без замены
	inputString = "who is there?";
	outputString = HtmlDecode(inputString);
	required = "who is there?";
	CHECK(outputString == required);

	inputString = "DDD&amp;FFF";
	outputString = HtmlDecode(inputString);
	required = "DDD&FFF";
	CHECK(outputString == required);
	
	inputString = "&quot;&amp;&quot;";
	outputString = HtmlDecode(inputString);
	required = "\"&\"";
	CHECK(outputString == required);

	inputString = "&lt;A&lt;B&quot;&amp;&quot;C&gt;D&gt;";
	outputString = HtmlDecode(inputString);
	required = "<A<B\"&\"C>D>";
	CHECK(outputString == required);
}
