#include "stdafx.h"
#include "dictionary.h"

int main(int argc, char** argv)
{

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	auto dictionaryFileName = parseArguments(argc, argv);

	if (!dictionaryFileName)
	{
		return 1;
	}

	WordsContainer dictionary;
	WordsContainer newWords;
	GetDictionaryFromFile(dictionaryFileName, dictionary);

	if (!ProcessUsersRequests(dictionary, newWords))
	{
		return 1;
	}

	if (SaveChangesToDictionary(dictionaryFileName, newWords))
	{
		return 0;
	}

	else
	{
		return 1;
	}
}