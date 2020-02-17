using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

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

int main(int argc, char* argv[])
{
	
	if (argc != 5)
	{
		cout << "Invalid argument count\n";
		cout <<"Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
	}

	ifstream inputFile;
	inputFile.open(argv[1]);

	ofstream outputFile;
	outputFile.open(argv[2]);


	string search = argv[3];
	string replace = argv[4];


	CopyFileWithReplace(inputFile, outputFile, search, replace);
	outputFile.flush();

	/*string s = "LateToStayHere";
	size_t foundPos = s.find("Lafte", 0);
	cout << foundPos;*/

	return 0;
}

