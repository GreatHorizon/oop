
struct DictionaryPath
{
	std::string dictionaryFileName;
};

typedef std::multimap <std::string, std::string> WordsContainer;
const std::string END_PROGRAMM_COMMAND = "...";
const std::string UPPER_CASE_COMMAND_TO_SAVE = "Y";
const std::string LOWER_CASE_COMMAND_TO_SAVE = "y";
const int ARGUMENTS_COUNT = 2;

std::optional <DictionaryPath> parseArguments(int argc, char** argv);
bool SearchTranslation(const std::string& word, std::string& translation, WordsContainer dictionary);
void GetTranslation(const std::string& word, std::string& translation, WordsContainer container);
bool GetDictionaryFromFile(std::optional <DictionaryPath>& dictionaryArgs, WordsContainer& dictionary);
bool PushNewWordsToFile(const std::string& dictionaryFileName, WordsContainer& newWords);
bool SaveChangesToDictionary(std::optional <DictionaryPath>& dictionaryArgs, WordsContainer& newWords);
void PushWordsToDictionary(WordsContainer& newWords, const std::string& word, std::string& translation, WordsContainer& dictionary);
void AddNewWordToDictionary(const std::string& word, std::string& translation,
	WordsContainer& newWords, WordsContainer& dictionary);
bool ProcessUsersRequests(WordsContainer& dictionary, WordsContainer& newWords);

