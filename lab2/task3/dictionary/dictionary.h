#pragma once
#include "stdafx.h"
#include "dictionary.cpp"

const string END_PROGRAMM_COMMAND = "...";
const string DEFAULT_FILE_NAME = "dictionary.txt";

typedef multimap <string, string> WordsContainer;

optional <string> parseArguments(int argc, char** argv);
bool GetTranstationFromDictionary(const string& word, string& translation,
    WordsContainer dictionary, WordsContainer newWords);
void getTranslation(const string& word, string& translation, WordsContainer container);
void GetDictionaryFromFile(string dictionaryFileName, WordsContainer& dictionary);
bool PushNewWordsToFile(const string& dictionaryFileName, WordsContainer& newWords);
bool SaveChangesToDictionary(const string& dictionaryFileName, WordsContainer& newWords);
void AddNewWordToTheDictionary(const string& word, WordsContainer& newWords);
bool ProcessUsersRequests(WordsContainer& dictionary, WordsContainer& newWords);

