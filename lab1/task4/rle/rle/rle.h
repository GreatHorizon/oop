enum class Mode
{
	PACK_MODE,
	UNPACK_MODE,
	INCORRECT_MODE,
};

struct RLEPacket
{
	uint8_t currentByte;
	uint8_t byteCounter;
};

struct Arguments
{
	std::string inputFileName;
	std::string outputFileName;
	Mode mode = Mode::INCORRECT_MODE;
};

Mode GetMode(std::string mode);
std::optional <Arguments> ParseArguments(const int argc, char** argv);
bool CheckFileSize(std::istream& inputFile);
void PutPairOfBytes(std::ostream& outputFile, RLEPacket packet);
void PackCurrentByte(RLEPacket& packet, char byte, std::ostream& outputFile);
void PackData(std::istream& inputFile, std::ostream& outputFile);
bool PackFile(const std::string& inputFileName, const std::string& outputFileName);
void UnpackData(std::istream& inputFile, std::ostream& outputFile);
bool UnpackFile(const std::string& inputFileName, const std::string& outputFileName);
