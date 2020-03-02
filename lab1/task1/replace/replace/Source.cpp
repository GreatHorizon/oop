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
	args.searchString = argv[3];
	args.replaceString = argv[4];
	
	return args;
}

string ReplaceString(const string& subject,
	const string& searchString, const string& replacementString)
{
	size_t pos = 0;
	size_t foundPos = 0;
	string result;

	while (pos < subject.length())
	{
		foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);

		if (foundPos != string::npos)
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

bool CopyFileWithReplace(istream& inputFile, ostream& outputFile, 
	const string& searchString, const string& replacementString)
{
	string line;

	while (getline(inputFile, line))
	{
		outputFile << ReplaceString(line, searchString, replacementString) << endl;
	}

	if (inputFile.bad())
	{
		cout << "Failed to read data from input file" << endl;
		return false;
	}

	if (!outputFile.flush())
	{
		cout << "Failed to write data in output file" << endl;
		return false;
	}

	return true;
}

bool checkFilesAndShowErrors(optional<Args> args, ifstream& inputFile, ofstream& outputFile)
{
	if (!args)
	{
		cout << "Invalid argument count"<< endl;
		cout << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>" << endl;
		return false;
	}

	if (args->searchString.empty())
	{
		cout << "<searchString> should not be empty" << endl;
		return false;
	}

	inputFile.open(args->inputFileName);
	outputFile.open(args->outputFileName);

	if (!inputFile.is_open())
	{
		cout << "Failed to open " << args->inputFileName << " for reading" << endl;
		return false;
	}

	if (!outputFile.is_open())
	{
		cout << "Failed to open " << args->outputFileName << " for writing" << endl;
		return false;
	}

	return true;
}

int main(int argc, char** argv)
{
	optional args = ParseArguments(argc, argv);
	ifstream inputFile;
	ofstream outputFile;

	if (!checkFilesAndShowErrors(args, inputFile, outputFile))
	{
		return 1;
	}

	if (!CopyFileWithReplace(inputFile, outputFile, args->searchString, args->replaceString))
	{
		return 1;
	}

	return 0;
}

