#pragma once
#include "stdafx.h"


struct DictionaryInfo
{
	std::string dictionaryFileName;
	bool isDictionary;
};

const std::string END_PROGRAMM_COMMAND = "...";
const std::string DEFAULT_FILE_NAME = "dictionary.txt";

typedef std::multimap <std::string, std::string> WordsContainer;

std::optional <DictionaryInfo> parseArguments(int argc, char** argv);
bool SearchTranslation(const std::string& word, std::string& translation,
    WordsContainer dictionary, WordsContainer newWords);
void GetNewFileName(std::optional <DictionaryInfo>& dictionaryArg);
void getTranslation(const std::string& word, std::string& translation, WordsContainer container);
bool GetDictionaryFromFile(std::optional <DictionaryInfo>& dictionaryArgs, WordsContainer& dictionary);
void RemoveDuplicate(std::pair<WordsContainer::iterator, WordsContainer::iterator>& positions, WordsContainer::iterator& it, WordsContainer& newWords);
bool PushNewWordsToFile(const std::string& dictionaryFileName, WordsContainer& newWords);
bool SaveChangesToDictionary(std::optional <DictionaryInfo>& dictionaryArgs, WordsContainer& newWords);
void AddNewWordToTheDictionary(const std::string& word, WordsContainer& newWords);
bool ProcessUsersRequests(WordsContainer& dictionary, WordsContainer& newWords);

