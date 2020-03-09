
#include <iostream>
#include <fstream>
#include <optional>

using namespace std;

const int ARGUMENTS_COUNT = 4;
const int MAX_BYTE_AMOUNT = 255;
const string PACK_MODE_ARGUMENT = "pack";
const string UNPACK_MODE_ARGUMENT = "unpack";

enum class Mode
{
	PACK_MODE,
	UNPACK_MODE,
	INCORRECT_MODE,
};

struct Arguments
{
	string inputFileName;
	string outputFileName;
	Mode mode;
};


Mode GetMode(string mode)
{
	if (mode == PACK_MODE_ARGUMENT)
	{
		return Mode::PACK_MODE;
	}

	if (mode == UNPACK_MODE_ARGUMENT)
	{
		return Mode::UNPACK_MODE;
	}

	else
	{
		cout << "Incorrect pack mode" << endl;
		cout << "Mode should be <pack> or <unpack>" << endl;
		return Mode::INCORRECT_MODE;
	}
}
 
optional <Arguments> ParseArguments(const int argc, char** argv)
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: <mode> <inputFileName> <outputFileName>" << endl;
		return nullopt;
	}

	Arguments args;

	args.mode = GetMode(argv[1]);
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	return args;
}

void PutPairOfBytes(ostream& outputFile, char currentByte, unsigned char byteAmount)
{
	outputFile.put(byteAmount);
	outputFile.put(currentByte);
}

void PackData(ifstream& inputFile, ofstream& outputFile)
{
	char currentByte = 0;
	char nextByte = 0;
	unsigned char byteCounter = 1;

	while (inputFile.read(&nextByte, sizeof(nextByte)))
	{
		if (currentByte == 0)
		{
			currentByte = nextByte;
			continue;
		}

		if (nextByte == currentByte && byteCounter < MAX_BYTE_AMOUNT)
		{
			byteCounter++;
		}

		else
		{
			PutPairOfBytes(outputFile, currentByte, byteCounter);
			currentByte = nextByte;
			byteCounter = 1;
		}

		if (inputFile.peek() == -1)
		{
			PutPairOfBytes(outputFile, currentByte, byteCounter);
		}
	}
}

bool PackFile(string inputFileName, string outputFileName)
{
	ofstream outputFile;
	ifstream inputFile;

	inputFile.open(inputFileName, ios::binary | ios::ate);
	outputFile.open(outputFileName, ios::binary);

	if (!inputFile.is_open())
	{
		cout << "Failed to open" << inputFileName << "for reading";
		return false;
	}

	if (!outputFile.is_open())
	{
		cout << "Failed to open" <<	outputFileName << "for writing";
		return false;
	}

	if (!inputFile.tellg())
	{
		cout << "Input file should not be empty" << endl;
		return false;
	}

	inputFile.seekg(0, ios::beg);

	PackData(inputFile, outputFile);
	return true;
}



void unpackData(ifstream& inputFile, ofstream& outputFile)
{
	char byteCount = 0;
	char currentByte;
	int byteAmount = 0;

	while (inputFile.read(&byteCount, sizeof(byteCount)))
	{
		byteAmount = static_cast<int>(static_cast<unsigned char>(byteCount));
		inputFile.read(&currentByte, sizeof(currentByte));
		for (int i= 0;  i < byteAmount; ++i)
		{
			outputFile << currentByte;
		}

	}
}

bool UnpackFile(string inputFileName, string outputFileName)
{
	ofstream outputFile;
	ifstream inputFile;

	inputFile.open(inputFileName, ios::binary | ios::ate);
	outputFile.open(outputFileName, ios::binary);

	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading"<< endl;
		return false;
	}

	if (!outputFile.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing" << endl;
		return false;
	}

	streampos inputFileSize = inputFile.tellg();

	if (!inputFileSize)
	{
		cout << "Input file should not be empty" << endl;
		return false;
	}

	if (inputFileSize % 2 != 0)
	{
		cout << "Input file should have even byte amount" << endl;
		return false;
	}

	inputFile.seekg(0);
	unpackData(inputFile, outputFile);

	if (inputFile.bad())
	{
		cout << "Failed to read data from "<< inputFileName << endl;
		return false;
	}

	if (!outputFile.flush())
	{
		cout << "Failed to write data to " << outputFileName << endl;
		return false;
	}

	return true;
}

int main(int argc, char** argv)
{
	optional args = ParseArguments(argc, argv);

	if (!args)
	{
		return 1;
	}

	if (args->mode == Mode::INCORRECT_MODE)
	{
		return 1;
	}

	if (args->mode == Mode::PACK_MODE)
	{
		if (!PackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}
	else
	{
		if (!UnpackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}
	

	return 0;
}






