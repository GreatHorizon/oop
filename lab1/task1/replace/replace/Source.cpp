using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <optional>


struct Args
{
	string inputFileName;
	string outputFileName;
	string searchString;
	string replaceString;
};

optional<Args> ParseArguments(int argc, char** argv)
{
	if (argc != 5)
	{
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.replaceString = argv[3];
	args.searchString = argv[4];
	return args;
}

string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

void CopyFileWithReplace(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

int main(int argc, char** argv)
{
	optional args = ParseArguments(argc, argv);

	if (!args)
	{
		cout << "Invalid argument count\n";
		cout <<"Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	ifstream inputFile;
	ofstream outputFile;

	inputFile.open(args->inputFileName);
	outputFile.open(args->outputFileName);

	if (!inputFile.is_open())
	{
		cout << "Failed to open " << args->inputFileName << " for reading" << endl;
		return 1;
	}

	if (!outputFile.is_open())
	{
		cout << "Failed to open " << args->outputFileName << " for w" << endl;
		return 1;
	}

	string search = args->searchString;
	string replace = args->replaceString;


	CopyFileWithReplace(inputFile, outputFile, search, replace);
	outputFile.flush();

	/*string s = "LateToStayHere";
	size_t foundPos = s.find("Lafte", 0);
	cout << foundPos;*/

	return 0;
}

