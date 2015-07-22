#include <iostream>
#include <vector>
#include <map>

using namespace std;

int numCalls = 0;

int longestIncreasingSequence(vector<int>& sequence, int min, vector<int>& result)
{
	++numCalls;

	if (sequence.size() == 0)
	{
		return 0;
	}

	int max = 0;

	int back = sequence.back();
	vector<int> result1;
	vector<int> result2;
	if (back > min)
	{
		sequence.pop_back();
		int tmp = longestIncreasingSequence(sequence, back, result1);
		max = tmp + 1;
		sequence.push_back(back);
		
	}

	sequence.pop_back();
	int tmp = longestIncreasingSequence(sequence, min, result2);
	sequence.push_back(back);

	if (tmp > max)
	{
		max = tmp;
		result = result2;
	}
	else
	{
		result1.push_back(back);
		result = result1;
	}

	return max;
}

int Longest_Increasing_Sequence()
{
	vector<int> sequence = { 10, 3, 5, 2, 5, 7, 9, 1, 5, 2, 9, 4, 6, 2, 10};
	// vector<int> sequence = { 10, 9, 8, 5, 6, 3, 2, 4, 1, 2 };
	
	vector<int> result;

	cout << longestIncreasingSequence(sequence, 0, result) << endl;
	cout << numCalls << endl;
	for (int i = 0; i < result.size(); ++i)
	{
		cout << result[i] << " ";
	}

	int test;
	cin >> test;

	return 0;
}