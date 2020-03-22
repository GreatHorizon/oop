#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary/dictionary.h"
using namespace std;

TEST_CASE("Test SearchTranslation()")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string translation;
	WordsContainer dictionary = {
		{ "cat", "кошка" },
		{"apple", "яблоко"},
		{ "snake", "змея"},
		{ "dog",  "собака"},
		{ "dog", "пес"},
		{"машина", "car"}
	};
	
	SearchTranslation("dog", translation, dictionary);
	REQUIRE(translation == "собака, пес");
	SearchTranslation("snake", translation, dictionary);
	REQUIRE(translation == "змея");
	SearchTranslation("кот", translation, dictionary);
	REQUIRE(translation == "");
	SearchTranslation("snake", translation, dictionary);
	REQUIRE(translation == "змея");
	SearchTranslation("машина", translation, dictionary);
	REQUIRE(translation == "car");
}

TEST_CASE("Test AddNewWordToDictionary()")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string translation;
	WordsContainer newWords;
	WordsContainer dictionary = {
		{ "cat", "кошка" },
		{"apple", "яблоко"},
		{ "snake", "змея"},
		{ "dog",  "собака"},
		{ "dog", "пес"},
		{"машина", "car"}
	};

	//Поиск перед добавлением слова "grass"
	SearchTranslation("grass", translation, dictionary);
	REQUIRE(translation == "");

	translation = "трава";
	AddNewWordToDictionary("grass", translation , newWords, dictionary);
	SearchTranslation("grass", translation, dictionary);
	REQUIRE(translation == "трава");

	//Поиск "cat" перед обавлением слова "кот" с переводом "cat"
	SearchTranslation("cat", translation, dictionary);
	REQUIRE(translation == "кошка");

	translation = "cat";
	AddNewWordToDictionary("кот", translation, newWords, dictionary);
	SearchTranslation("cat", translation, dictionary);
	REQUIRE(translation == "кошка, кот");
}