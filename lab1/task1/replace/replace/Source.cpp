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

enum State {
	CHECK_BEFORE_COPYING,
	CHECK_AFTER_COPYING,
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
	string result;

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
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

void CopyFileWithReplace(istream& input, ostream& output, 
	const string& searchString, const string& replacementString)
{
	string line;

	while (getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << endl;
	}
}

//void ShowError(Error error, optional<Args> args)
//{
//	if (error == TOO_FEW_ARGUMENTS)
//	{
//		cout << "Invalid argument count\n";
//		cout << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
//		return;
//	}
//
//	if (error == INPUT_FILE_OPENING_ERROR)
//	{
//		cout << "Failed to open " << args->inputFileName << " for reading" << endl;
//		return;
//	}
//
//	if (error == OUTPUT_FILE_OPENING_ERROR)
//	{
//		cout << "Failed to open " << args->outputFileName << " for writing" << endl;
//		return;
//	}
//
//	if (error == SEARCH_STRING_IS_EMPRY)
//	{
//		cout << "<searchString> should not be empty" << endl;
//		return;
//	}
//}

bool checkFilesAndShowErrors(optional<Args> args, ifstream& inputFile, ofstream& outputFile, State state)
{
	if (state == CHECK_BEFORE_COPYING)
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
	}
	else
	{
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
	}

	return true;
}

int main(int argc, char** argv)
{
	optional args = ParseArguments(argc, argv);
	ifstream inputFile;
	ofstream outputFile;

	if (!checkFilesAndShowErrors(args, inputFile, outputFile, CHECK_BEFORE_COPYING))
	{
		return 1;
	}

	CopyFileWithReplace(inputFile, outputFile, args->searchString, args->replaceString);

	if (!checkFilesAndShowErrors(args, inputFile, outputFile, CHECK_AFTER_COPYING))
	{
		return 1;
	}

	return 0;
}

