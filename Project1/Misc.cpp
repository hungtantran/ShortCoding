#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <sstream>
#include <string>
#include <set>

using namespace std;

int longest_1_sequence(const std::vector<int>& input)
{
	vector<int> maxFromRight;
	maxFromRight.resize(input.size());

	int maxFromRightSoFar = 0;
	for (int i = input.size() - 1; i >= 0; --i)
	{
		maxFromRight[i] = maxFromRightSoFar;

		if (input[i] == 1)
		{
			++maxFromRightSoFar;
		}
		else
		{
			maxFromRightSoFar = 0;
		}
	}

	int maxSizeSofar = 0;
	int maxIndexSofar = -1;
	int numOnesToTheLeft = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == 0)
		{
			if (numOnesToTheLeft + 1 + maxFromRight[i] > maxSizeSofar)
			{
				maxIndexSofar = i;
				maxSizeSofar = numOnesToTheLeft + 1 + maxFromRight[i];
			}

			numOnesToTheLeft = 0;
		}
		else
		{
			++numOnesToTheLeft;
		}
	}

	return maxIndexSofar;
}

void total_number_of_non_decreasing_numbers_with_n_digits(int n, int& result, int min)
{
	if (n == 0)
	{
		++result;
		return;
	}

	for (int i = min; i < 10; ++i)
	{
		total_number_of_non_decreasing_numbers_with_n_digits(n - 1, result, i);
	}
}

void total_number_of_non_decreasing_numbers_with_n_digits(int n, int& result)
{
	total_number_of_non_decreasing_numbers_with_n_digits(n, result, 0);
}

bool find_if_subsequence(const string& str1, const string& str2, int index1, int index2)
{
	if (str1.length() == 0 || index1 == str1.length())
	{
		return true;
	}

	if (index2 >= str2.length())
	{
		return false;
	}

	if (str1[index1] == str2[index2])
	{
		return true;
	}

	return find_if_subsequence(str1, str2, index1, index2 + 1);
}

bool find_if_subsequence(const string& str1, const string& str2)
{
	return find_if_subsequence(str1, str2, 0, 0);
}

int snake_ladder(const vector<int>& moves, int index, set<int>& steps, map<int, int>& cost)
{
	if (index >= moves.size() - 1)
	{
		return 0;
	}

	if (steps.find(index) != steps.end())
	{
		return INT_MAX;
	}

	if (cost.find(index) != cost.end())
	{
		return cost.at(index);
	}

	steps.insert(index);
	steps.insert(moves[index]);

	int minSteps = INT_MAX;
	for (int i = 6; i >= 0; --i)
	{
		if (index + i >= moves.size() - 1)
		{
			return 0;
		}

		int numSteps = INT_MAX;
		if (moves[index + i] != -1)
		{
			numSteps = snake_ladder(moves, moves[index + i], steps, cost);
			cost[moves[index + i]] =  numSteps;
		}
		else
		{
			numSteps = snake_ladder(moves, index + i, steps, cost);
			cost[index + i] = numSteps;
		}

		if (numSteps < INT_MAX && minSteps > numSteps + 1)
		{
			minSteps = numSteps + 1;
		}
	}

	steps.erase(index);
	steps.erase(moves[index]);

	return minSteps;
}

int snake_ladder(const vector<int>& moves)
{
	set<int> steps;
	map<int, int> cost;
	return snake_ladder(moves, 0, steps, cost);
}

// http://www.geeksforgeeks.org/find-index-0-replaced-1-get-longest-continuous-sequence-1s-binary-array/
// int main()
int longest_1_sequence()
{
	vector<int> input1 = { 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1 };
	cout << longest_1_sequence(input1) << endl;

	vector<int> input2 = { 1, 1, 1, 1, 0 };
	cout << longest_1_sequence(input2) << endl;

	int test;
	cin >> test;

	return 0;
}

// http://www.geeksforgeeks.org/total-number-of-non-decreasing-numbers-with-n-digits/
// int main()
int total_number_of_non_decreasing_numbers_with_n_digits()
{
	int total = 0;
	total_number_of_non_decreasing_numbers_with_n_digits(1, total);
	cout << total << endl;

	total = 0;
	total_number_of_non_decreasing_numbers_with_n_digits(2, total);
	cout << total << endl;

	total = 0;
	total_number_of_non_decreasing_numbers_with_n_digits(3, total);
	cout << total << endl;

	total = 0;
	total_number_of_non_decreasing_numbers_with_n_digits(4, total);
	cout << total << endl;

	int test;
	cin >> test;

	return 0;
}

// http://www.geeksforgeeks.org/given-two-strings-find-first-string-subsequence-second/
// int main()
int find_if_subsequence()
{
	string str1 = "AXY";
	string str2 = "ADXCPY";
	cout << find_if_subsequence(str1, str2) << endl;

	str1 = "AXY";
	str2 = "YADXCP";
	cout << find_if_subsequence(str1, str2) << endl;

	str1 = "gksrek";
	str2 = "geeksforgeeks";
	cout << find_if_subsequence(str1, str2) << endl;

	int test;
	cin >> test;

	return 0;
}

// http://www.geeksforgeeks.org/snake-ladder-problem-2/
// int main()
int snake_ladder()
{
	vector<int> moves;
	moves.resize(30);

	for (int i = 0; i < 30; i++)
	{
		moves[i] = -1;
	}

	// Ladders
	moves[2] = 21;
	moves[4] = 7;
	moves[10] = 25;
	moves[19] = 28;

	// Snakes
	moves[26] = 0;
	moves[20] = 8;
	moves[16] = 3;
	moves[18] = 6;

	cout << snake_ladder(moves) << endl;

	int test;
	cin >> test;

	return 0;
}
