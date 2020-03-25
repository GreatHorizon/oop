#include "stdafx.h"
#include "dictionary.h"

using namespace std;

void GetTranslation(const string& word, string& translation, WordsContainer container)
{
	auto positions = container.equal_range(word);
	for (auto it = positions.first ; it != positions.second; it++)
	{
		if (it != positions.first)
		{
			translation += ", ";
		}

		if (it->first == word)
		{
			translation += it->second;
		}
		else
		{
			break;
		}
	}
}

bool SearchTranslation(const string& word, string& translation, WordsContainer dictionary)
{
	translation = "";
	auto foundWordPosition = dictionary.find(word);

	if (foundWordPosition != dictionary.end())
	{
		GetTranslation(word, translation, dictionary);
		return true;
	}
	else
	{
		return false;
	}
}

bool GetDictionaryFromFile(optional <DictionaryPath>& dictionaryArgs, WordsContainer& dictionary)
{
	ifstream dictionaryFile;
	dictionaryFile.open(dictionaryArgs->dictionaryFileName);

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
				dictionary.insert(make_pair(word, translation));
				dictionary.insert(make_pair(translation, word));
			}	
		}
	}

	if (dictionaryFile.bad())
	{
		return false;
		cout << "There was an error while reading file" << endl;
	}

	return true;
}

bool PushNewWordsToFile(const string& dictionaryFileName, WordsContainer& newWords)
{
	ofstream dictionaryFile;
	dictionaryFile.open(dictionaryFileName, ios::app);

	if (!dictionaryFile.is_open())
	{
		cout << "Failed to open " << dictionaryFileName <<" for writing data." <<endl;
		return false;
	}

	for (auto it = newWords.begin(); it != newWords.end(); ++it)
	{
		dictionaryFile << it->first << endl;
		dictionaryFile << it->second << endl;
	}

	if (!dictionaryFile.flush())
	{
		cout << "Failed to write data to " << dictionaryFileName << endl;
		return false;
	}

	return true;
}

bool SaveChangesToDictionary(optional <DictionaryPath>& dictionaryArg, WordsContainer& newWords)
{
	string word;
	cout << "Dictionary was changed. Enter Y or y to save or empty string to end program." << endl;
	getline(cin, word);
	if (word == LOWER_CASE_COMMAND_TO_SAVE || word == UPPER_CASE_COMMAND_TO_SAVE)
	{	
		if (PushNewWordsToFile(dictionaryArg->dictionaryFileName, newWords))
		{
			cout << "Changes was saved. Goodbye." << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout <<  "Changes was not saved. Goodbye." << endl;
		return true;
	}
}

void PushWordsToDictionary(WordsContainer& newWords, const string& word,
	string& translation, WordsContainer& dictionary)
{
	newWords.insert(make_pair(word, translation));
	dictionary.insert(make_pair(word, translation));
	dictionary.insert(make_pair(translation, word));
}

void AddNewWordToDictionary(const string& word, string& translation,
	WordsContainer& newWords, WordsContainer& dictionary)
{
	if (translation.empty())
	{
		cout << "Word " << "\"" << word << "\"" << " was ignored."<<endl;
	}
	else
	{
		PushWordsToDictionary(newWords, word, translation, dictionary);
		cout << "Word " << "\"" << word << "\"" << " with translation " <<"\""
			<< translation<<"\" " << "was added to the dictionary"<<endl;
	}
}

bool ProcessUsersRequests(WordsContainer& dictionary, WordsContainer& newWords)
{
	string word, translation;
	bool result = false;

	cout << "Enter word to translate" << endl;
	while (getline(cin, word) && word != END_PROGRAMM_COMMAND)
	{
		if (word.empty())
		{
			cout << "Invalid command, enter word to translate"<<endl;
			cout << "Or " << "..." << "to end program" << endl;
			continue;
		}

		if (SearchTranslation(word, translation, dictionary))
		{
			cout << translation << endl;
		}
		else
		{
			cout << "Unknown word " << "\"" << word << "\". "
				<< "Enter translation or empry string to ignore" << endl;
			getline(cin, translation);
			AddNewWordToDictionary(word, translation, newWords, dictionary);
			result = true;
		}	
	}

	return result;
}