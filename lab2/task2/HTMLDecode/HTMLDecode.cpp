#include "stdafx.h"
#include "implementation.h"
using namespace std;

int main()
{
	string inputString;

	while (getline(cin, inputString))
	{
		cout << HtmlDecode(inputString) << endl;
	}

	return 0;
}