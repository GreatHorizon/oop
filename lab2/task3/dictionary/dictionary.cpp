#include "stdafx.h"
#include "dictionary.h"
using namespace std;

const std::string END_PROGRAMM_COMMAND = "...";

optional <DictionaryInfo> parseArguments(int argc, char** argv)
{
	DictionaryInfo dictionaryArg;
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

bool GetDictionaryFromFile(optional <DictionaryInfo>& dictionaryArgs, WordsContainer& dictionary)
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

void RemoveDuplicate(pair<WordsContainer::iterator, WordsContainer::iterator>& positions, 
	WordsContainer::iterator& it, WordsContainer& newWords)
{
	for (auto iterator = positions.first; iterator != positions.second; iterator++)
	{
		if (iterator->second == it->first)
		{
			newWords.erase(iterator);
			break;
		}
	}
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
		
		auto positions = newWords.equal_range(it->second);
		RemoveDuplicate(positions, it, newWords);
	}

	if (!dictionaryFile.flush())
	{
		cout << "Failed to write data to " << dictionaryFileName << endl;
		return false;
	}

	return true;
}

bool SaveChangesToDictionary(optional <DictionaryInfo>& dictionaryArg, WordsContainer& newWords)
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

void PushWordsToDictionary(WordsContainer& newWords, const string& word,
	string& translation, WordsContainer& dictionary)
{
	newWords.insert(make_pair(word, translation));
	newWords.insert(make_pair(translation, word));
	dictionary.insert(make_pair(word, translation));
	dictionary.insert(make_pair(translation, word));
}

void AddNewWordToDictionary(const string& word, string& translation,
	WordsContainer& newWords, WordsContainer& dictionary)
{
	if (translation.empty())
	{
		cout << "Слово " << "\"" << word << "\"" << " проигнорировано."<<endl;
	}
	else
	{
		PushWordsToDictionary(newWords, word, translation, dictionary);
		cout << "Слово " << "\"" << word << "\"" << " с переводом " <<"\""
			<< translation<<"\" " << "добавлено в словарь."<<endl;
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
			cout << "Или " << "..." << "для выхода из программы" << endl;
			continue;
		}

		if (SearchTranslation(word, translation, dictionary))
		{
			cout << translation << endl;
		}
		else
		{
			cout << "Неизвестное слово " << "\"" << word << "\". "
				<< "Введите перевод или пустую строку для отказа." << endl;
			getline(cin, translation);
			AddNewWordToDictionary(word, translation, newWords, dictionary);
			result = true;
		}	
	}
	return result;
}