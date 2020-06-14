#pragma once
#include <vector>

template <class T, class Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr.front();
	for (auto& element : arr)
	{
		if (less(maxValue, element))
		{
			maxValue = element;
		}
	}

	return true;
}

