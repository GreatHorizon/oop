#include "../dictionary/stdafx.h"
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary/dictionary.h"
using namespace std;

TEST_CASE("Test SearchTranslation()")
{
	string translation;
	Words words;
	words.vocabulary = {
		{ "cat", "кошка" },
		{"apple", "яблоко"},
		{ "snake", "змея"},
		{ "dog",  "собака"},
		{ "dog", "пес"},
		{"машина", "car"}
	};
	
	REQUIRE(SearchTranslation("dog", words.vocabulary).value() == "собака, пес");
	REQUIRE(SearchTranslation("snake", words.vocabulary).value() == "змея");
	REQUIRE(SearchTranslation("кот", words.vocabulary) == nullopt);
	REQUIRE(SearchTranslation("apple", words.vocabulary).value() == "яблоко");
	REQUIRE(SearchTranslation("машина", words.vocabulary).value() == "car");
}

TEST_CASE("Test AddNewWordToDictionary()")
{
	Words words;
	words.vocabulary = {
		{ "cat", "кошка" },
		{"apple", "яблоко"},
		{ "snake", "змея"},
		{ "dog",  "собака"},
		{ "dog", "пес"},
		{"машина", "car"}
	};

	//Поиск перед добавлением слова "grass"
	REQUIRE(SearchTranslation("grass", words.vocabulary) == nullopt);

	AddNewWordToDictionary("grass", "трава", words);
	REQUIRE(SearchTranslation("grass", words.vocabulary).value() == "трава");

	//Поиск "cat" перед обавлением слова "кот" с переводом "cat"
	REQUIRE(SearchTranslation("cat", words.vocabulary).value() == "кошка");

	AddNewWordToDictionary("кот", "cat", words);
	REQUIRE(SearchTranslation("cat", words.vocabulary).value() == "кошка, кот");
}