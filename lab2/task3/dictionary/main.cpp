#include "dictionary.h"

int main(int argc, char** argv)
{
	/*setlocale(LC_ALL, "Russian");*/
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