#include "stdafx.h"
#include "rle.h"
using namespace std;

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