#include "CMyList.h"
#include "stdafx.h"
#include <vector>

int main()
{
	CMyList<std::string> list;
	list.Append("1");
	list.Append("2");
	list.Append("3");
	list.Append("4");
	list.Append("5");
	list.Append("6");

	list.Clear();
	return 0;
}