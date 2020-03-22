#include "stdafx.h"
#include "dictionary.h"

using namespace std;

optional <DictionaryPath> parseArguments(int argc, char** argv)
{
	DictionaryPath dictionaryArg;
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: <dictionaryFileName>" << endl;
		return nullopt;
	}
	else
	{
		dictionaryArg.dictionaryFileName = argv[1];
	}
	return dictionaryArg;
};

int main(int argc, char** argv)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	auto dictionaryArg = parseArguments(argc, argv);
	WordsContainer dictionary;

	if (!dictionaryArg)
	{
		return 1;
	}

	if (!GetDictionaryFromFile(dictionaryArg, dictionary))
	{
		return 1;
	}

	WordsContainer newWords;
	if (!ProcessUsersRequests(dictionary, newWords))
	{
		return 1;
	}

	if (SaveChangesToDictionary(dictionaryArg, newWords))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}