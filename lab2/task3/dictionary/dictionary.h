#pragma once
#include "stdafx.h"


struct DictionaryInfo
{
	std::string dictionaryFileName;
};

const std::string END_PROGRAMM_COMMAND = "...";
const std::string DEFAULT_FILE_NAME = "dictionary.txt";

typedef std::multimap <std::string, std::string> WordsContainer;

std::optional <DictionaryInfo> parseArguments(int argc, char** argv);
bool GetTranstationFromDictionary(const std::string& word, std::string& translation,
    WordsContainer dictionary, WordsContainer newWords);
void getTranslation(const std::string& word, std::string& translation, WordsContainer container);
void GetDictionaryFromFile(std::optional<DictionaryInfo>& dictionaryArgs, WordsContainer& dictionary);
bool PushNewWordsToFile(const std::string& dictionaryFileName, WordsContainer& newWords);
bool SaveChangesToDictionary(std::optional<DictionaryInfo>& dictionaryArgs, WordsContainer& newWords);
void AddNewWordToTheDictionary(const std::string& word, WordsContainer& newWords);
bool ProcessUsersRequests(WordsContainer& dictionary, WordsContainer& newWords);

