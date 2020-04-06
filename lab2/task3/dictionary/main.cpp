#include "stdafx.h"
#include "dictionary.h"

using namespace std;

optional <string> ParseArguments(int argc, char** argv)
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" << "\n";
		cout << "Usage: <dictionaryFileName>" << "\n";
		return nullopt;
	}

	return argv[1];
};

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	auto dictionaryFileName = ParseArguments(argc, argv);
	Words words;

	if (!dictionaryFileName)
	{
		return 1;
	}

	if (!GetDictionaryFromFile(dictionaryFileName.value(), words.vocabulary))
	{
		return 1;
	}

	if (!ProcessUsersRequests(words))
	{
		return 1;
	}

	if (SaveChangesToDictionary(dictionaryFileName.value(), words.newWords))
	{
		return 0;
	}
	else
	{
		return 1;
	}	
}