#include "stdafx.h"
#include "dictionary.h"

using namespace std;

string GetTranslation(const string& word, const WordsContainer& container)
{
	string translation;
	auto positions = container.equal_range(word);
	for (auto it = positions.first ; it != positions.second; it++)
	{
		if (it != positions.first)
		{
			translation += ", ";
		}
		translation += it->second;
	}

	return translation;
}

optional<string> SearchTranslation(const string& word, const WordsContainer& dictionary)
{
	auto foundWordPosition = dictionary.find(word);

	if (foundWordPosition != dictionary.end())
	{
		return GetTranslation(word, dictionary);
	}
	else
	{
		return nullopt;
	}
}

bool GetDictionaryFromFile(const string& dictionaryFileName, WordsContainer& dictionary)
{
	ifstream dictionaryFile;
	dictionaryFile.open(dictionaryFileName);

	if (!dictionaryFile.is_open())
	{
		return true;
	}
	else
	{
		string word, translation;
		while (getline(dictionaryFile, word))
		{
			getline(dictionaryFile, translation);
			if (!word.empty() && !translation.empty())
			{
				dictionary.emplace(word, translation);
				dictionary.emplace(translation, word);
			}	
		}
	}

	if (dictionaryFile.bad())
	{
		cout << "There was an error while reading file" << "\n";
		return false;
	}

	return true;
}

bool PushNewWordsToFile(const string& dictionaryFileName, const WordsContainer& newWords)
{
	ofstream dictionaryFile;
	dictionaryFile.open(dictionaryFileName, ios::app);

	if (!dictionaryFile.is_open())
	{
		cout << "Failed to open " << dictionaryFileName <<" for writing data." << "\n";
		return false;
	}

	for (const auto& [word, translation] : newWords)
	{
		dictionaryFile << word << "\n";
		dictionaryFile << translation << "\n";
	}

	if (!dictionaryFile.flush())
	{
		cout << "Failed to write data to " << dictionaryFileName << "\n";
		return false;
	}

	return true;
}

bool SaveChangesToDictionary(string dictionaryFileName, const WordsContainer& newWords)
{
	string word;
	cout << "Dictionary was changed. Enter Y or y to save or empty string to end program." << "\n";
	getline(cin, word);
	if (word == "Y" || word == "y")
	{	
		if (dictionaryFileName.empty())
		{
			cout << "File name should not be empty" << "\n";
			cout << "Enter new file name" << "\n";
			getline(cin, dictionaryFileName);
		}

		if (PushNewWordsToFile(dictionaryFileName, newWords))
		{
			cout << "Changes was saved. Goodbye." << "\n";
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout <<  "Changes was not saved. Goodbye." << "\n";
		return true;
	}
}

void AddNewWordToDictionary(const string& word, const string& translation, Words& words)
{
	words.newWords.emplace(word, translation);
	words.vocabulary.emplace(word, translation);
	words.vocabulary.emplace(translation, word);
}

bool ProcessUsersRequests(Words& words)
{
	string word, translation;
	bool result = false;

	cout << "Enter word to translate" << "\n";
	while (getline(cin, word) && word != END_PROGRAMM_COMMAND)
	{
		if (word.empty())
		{
			cout << "Invalid command, enter word to translate"<< "\n";
			cout << "Or " << END_PROGRAMM_COMMAND << " to end program" << "\n";
			continue;
		}

		auto searchResult = SearchTranslation(word, words.vocabulary);

		if (!searchResult)
		{
			cout << "Unknown word " << "\"" << word << "\". ";
			cout << "Enter translation or empry string to ignore" << "\n";
			getline(cin, translation);

			if (!translation.empty())
			{
				AddNewWordToDictionary(word, translation, words);
				cout << "Word " << "\"" << word << "\"" << " with translation " << "\"";
				cout << translation << "\" " << "was added to the dictionary" << "\n";
				result = true;
			}
			else
			{
				cout << "Word " << "\"" << word << "\"" << " was ignored." << "\n";
			}
		}
		else
		{
			cout << searchResult.value() << "\n";
		}	
	}
	return result;
}