#include "stdafx.h"

unordered_map<string, string> entityList = {
	{"&amp;", "&"},
	{"&apos;", "`"},
	{"&lt;", "<"},
	{"&gt;", ">"},
	{"&quot;", "\""}
};

string ReplaceString(const string& subject, const string& searchString, const string& replacementString)
{
	size_t pos = 0;
	size_t foundPos = 0;
	string result;

	while (pos < subject.length())
	{
		foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);

		if (foundPos != string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

string HtmlDecode(const string& htmlString)
{
	string resultString = htmlString;

	for (unordered_map<string, string>::iterator it = entityList.begin(); it != entityList.end(); ++it)
	{
		resultString = ReplaceString(resultString, it->first, it->second);

	}

	return resultString;
}