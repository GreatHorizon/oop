#include "stdafx.h"
#include "rle.h"
using namespace std;

const int ARGUMENTS_COUNT = 4;
const int MAX_BYTE_AMOUNT = 255;
const string PACK_MODE = "pack";
const string UNPACK_MODE = "unpack";

Mode GetMode(string mode)
{
	if (mode == PACK_MODE)
	{
		return Mode::PACK_MODE;
	}

	if (mode == UNPACK_MODE)
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

bool CheckFileSize(istream& inputFile)
{
	streampos inputFileSize = inputFile.tellg();

	if (inputFileSize % 2 != 0)
	{
		return false;
	}

	inputFile.seekg(0);
	return true;
}

void PutPairOfBytes(ostream& outputFile, RLEPacket packet)
{
	outputFile.put(packet.byteCounter);
	outputFile.put(packet.currentByte);
}

void PackCurrentByte(RLEPacket& packet, char byte, ostream& outputFile)
{
	uint8_t data = byte;
	if (packet.currentByte == data && packet.byteCounter < MAX_BYTE_AMOUNT)
	{
		packet.byteCounter++;
	}
	else
	{
		PutPairOfBytes(outputFile, packet);
		packet.currentByte = data;
		packet.byteCounter = 1;
	}
}


void PackData(istream& inputFile, ostream& outputFile)
{
	RLEPacket packet;
	char byte = 0;

	inputFile.read(&byte, sizeof(byte));
	if (inputFile.eof())
	{
		return;
	}
	packet.currentByte = byte;
	packet.byteCounter = 1;

	while (inputFile.read(&byte, sizeof(byte)))
	{
		PackCurrentByte(packet, byte, outputFile);
	}

	PutPairOfBytes(outputFile, packet);

}

bool PackFile(const string& inputFileName, const string& outputFileName)
{
	ofstream outputFile;
	ifstream inputFile;

	inputFile.open(inputFileName, ios::binary | ios::ate);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputFileName << "for reading";
		return false;
	}

	outputFile.open(outputFileName, ios::binary);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " <<	outputFileName << "for writing";
		return false;
	}

	inputFile.seekg(0);
	PackData(inputFile, outputFile);

	if (inputFile.bad())
	{
		cout << "Failed to read data from " << inputFileName << endl;
		return false;
	}

	if (!outputFile.flush())
	{
		cout << "Failed to write data to " << outputFileName << endl;
		return false;
	}

	return true;
}

void UnpackData(istream& inputFile, ostream& outputFile)
{
	char byteCount = 0;
	char currentByte = 0;
	int byteAmount = 0;

	while (inputFile.read(&byteCount, sizeof(byteCount)))
	{
		byteAmount = static_cast<int>(static_cast<unsigned char>(byteCount));
		inputFile.read(&currentByte, sizeof(currentByte));
		for (int i = 0; i < byteAmount; ++i)
		{
			outputFile.put(currentByte);
		}
	}
}

bool UnpackFile(const string& inputFileName, const string& outputFileName)
{
	ofstream outputFile;
	ifstream inputFile;

	inputFile.open(inputFileName, ios::binary | ios::ate);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading"<< endl;
		return false;
	}

	outputFile.open(outputFileName, ios::binary);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing" << endl;
		return false;
	}

	if (!CheckFileSize(inputFile))
	{
		cout << "Input file should have even byte amount" << endl;
		return false;
	}

	UnpackData(inputFile, outputFile);

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

