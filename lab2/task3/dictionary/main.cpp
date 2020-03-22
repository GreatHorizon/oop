#include "dictionary.h"

int main(int argc, char** argv)
{

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	auto dictionaryArg = parseArguments(argc, argv);

	if (!dictionaryArg)
	{
		return 1;
	}

	WordsContainer dictionary;
	WordsContainer newWords;
	GetDictionaryFromFile(dictionaryArg, dictionary);

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