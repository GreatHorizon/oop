typedef std::multimap <std::string, std::string> WordsContainer;
const std::string END_PROGRAMM_COMMAND = "...";
const int ARGUMENTS_COUNT = 2;

struct Words
{
	WordsContainer newWords;
	WordsContainer vocabulary;
};

std::optional<std::string> SearchTranslation(const std::string& word, const WordsContainer& dictionary);
std::string GetTranslation(const std::string& word, const WordsContainer& container);
bool GetDictionaryFromFile(const std::string& dictionaryFileName, WordsContainer& dictionary);
bool PushNewWordsToFile(const std::string& dictionaryFileName, WordsContainer& newWords);
bool SaveChangesToDictionary(std::string dictionaryFileName, const WordsContainer& newWords);
void AddNewWordToDictionary(const std::string& word, const std::string& translation, Words& words);
bool ProcessUsersRequests(Words& words);

