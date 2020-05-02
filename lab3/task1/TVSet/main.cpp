#include "stdafx.h"
#include "TVSet.h"
#include "RemoteControl.h"

using namespace std;

int main()
{
	CTVSet tv;
	CRemoteControl remoteControl(tv, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		if (!remoteControl.HandleCommand())
		{
			cout << "Invalid command\n";
		}
	}

	return 0;
}