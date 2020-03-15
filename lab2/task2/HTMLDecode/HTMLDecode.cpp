#include "implementation.h"

int main()
{
	string inputString;

	while (getline(cin, inputString))
	{
		cout << HtmlDecode(inputString) << endl;
	}

	return 0;
}

