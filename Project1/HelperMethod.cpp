#include <time.h>
#include "HelperMethod.h"

using namespace std;

void HelperMethod::printArray(const vector<int>& arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
}

void HelperMethod::generateArray(vector<int>& arr, int size, int min, int max)
{
	for (int i = 0; i < size; ++i)
	{
		int val = rand() % (max - min + 1) + min;
		arr.emplace_back(val);
	}
}