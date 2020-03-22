#pragma once
#include "stdafx.h"

struct DictionaryInfo
{
	std::string dictionaryFileName;
};

typedef std::multimap <std::string, std::string> WordsContainer;

std::optional <DictionaryInfo> parseArguments(int argc, char** argv);
bool SearchTranslation(const std::string& word, std::string& translation, WordsContainer dictionary);
void GetTranslation(const std::string& word, std::string& translation, WordsContainer container);
bool GetDictionaryFromFile(std::optional <DictionaryInfo>& dictionaryArgs, WordsContainer& dictionary);
void RemoveDuplicate(std::pair<WordsContainer::iterator, WordsContainer::iterator>& positions, WordsContainer::iterator& it, WordsContainer& newWords);
bool PushNewWordsToFile(const std::string& dictionaryFileName, WordsContainer& newWords);
bool SaveChangesToDictionary(std::optional <DictionaryInfo>& dictionaryArgs, WordsContainer& newWords);
void PushWordsToDictionary(WordsContainer& newWords, const std::string& word, std::string& translation, WordsContainer& dictionary);
void AddNewWordToDictionary(const std::string& word, std::string& translation,
	WordsContainer& newWords, WordsContainer& dictionary);
bool ProcessUsersRequests(WordsContainer& dictionary, WordsContainer& newWords);

