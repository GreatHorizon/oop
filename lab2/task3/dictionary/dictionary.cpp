#include "stdafx.h"
#include "dictionary.h"

using namespace std;

optional <DictionaryInfo> parseArguments(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Invalid argument count" << endl;
		cout << "Usage: <dictionaryFileName>" << endl;
		return nullopt;
	}

	DictionaryInfo dictionaryArg;
	dictionaryArg.dictionaryFileName = argv[1];
	return dictionaryArg;
};

void getTranslation(const string& word, string& translation, WordsContainer container)
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

bool GetTranstationFromDictionary(const string& word, string& translation,
  WordsContainer dictionary, WordsContainer newWords)
{
	translation = "";
	auto foundWordPosition = dictionary.find(word);

	if (foundWordPosition != dictionary.end())
	{
		getTranslation(word, translation, dictionary);
	}
	else
	{
		foundWordPosition = newWords.find(word);
		if (foundWordPosition != newWords.end())
		{
			getTranslation(word, translation, newWords);
		}
		else
		{
			return false;
		}
	}

	return true;
}

void GetDictionaryFromFile(optional<DictionaryInfo>& dictionaryArgs, WordsContainer& dictionary)
{
	ifstream dictionaryFile;
	dictionaryFile.open(dictionaryArgs->dictionaryFileName);

	if (!dictionaryFile.is_open())
	{
		dictionaryArgs->dictionaryFileName = DEFAULT_FILE_NAME;
	}
	else
	{
		string word, translation;
		while (!dictionaryFile.eof())
		{
			getline(dictionaryFile, translation);
			if (!word.empty() && !translation.empty())
			{
				dictionary.insert(make_pair(word, translation));
				dictionary.insert(make_pair(translation, word));
			}	
		}
	}
}

bool PushNewWordsToFile(const string& dictionaryFileName, WordsContainer& newWords)
{
	ofstream dictionaryFile;
	dictionaryFile.open(dictionaryFileName, ios::app);

	if (!dictionaryFile.is_open())
	{
		cout << "Failed to write data to " << dictionaryFileName << endl;
		return false;
	}

	for (auto it = newWords.begin(); it != newWords.end(); ++it)
	{
		dictionaryFile << it->first << endl;
		dictionaryFile << it->second << endl;
		
		auto positions = newWords.equal_range(it->second);

		for (auto iterator = positions.first; iterator != positions.second; iterator++)
		{
			if (iterator->second == it->first)
			{
				newWords.erase(iterator);
				break;
			}
		}
	}
	return true;
}

bool SaveChangesToDictionary(optional<DictionaryInfo>& dictionaryArg, WordsContainer& newWords)
{
	string word;
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;
	getline(cin, word);
	if (word == "Y" || word == "y")
	{	
		if (PushNewWordsToFile(dictionaryArg->dictionaryFileName, newWords))
		{
			cout << "Изменения сохранены. До свидания." << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Изменения не были сохранены. До свидания." << endl;
		return true;
	}
}

void AddNewWordToTheDictionary(const string& word, WordsContainer& newWords)
{
	string translation;
	cout << "Неизвестное слово " << "\"" << word << "\". " 
		<< "Введите перевод или пустую строку для отказа." << endl;

	getline(cin, translation);

	if (translation.empty())
	{
		cout << "Слово " << "\"" << word << "\"" << " проигнорировано."<<endl;
	}
	else
	{
		newWords.insert(make_pair(word, translation));
		newWords.insert(make_pair(translation, word));
		cout << "Слово " << "\"" << word << "\"" << " с переводом " <<"\""<< translation<<"\" " << "добавлено в словарь."<<endl;
	}
}

bool ProcessUsersRequests(WordsContainer& dictionary, WordsContainer& newWords)
{
	string word, translation;
	bool result = false;

	cout << "Введите слово для перевода" << endl;
	while (getline(cin, word) && word != END_PROGRAMM_COMMAND)
	{
		if (word.empty())
		{
			cout << "Некорректная команда, введите слово для перевода"<<endl;
			continue;
		}

		if (GetTranstationFromDictionary(word, translation, dictionary, newWords))
		{
			cout << translation << endl;
		}
		else
		{
			AddNewWordToTheDictionary(word, newWords);
			result = true;
		}	
	}
	return result;
}


