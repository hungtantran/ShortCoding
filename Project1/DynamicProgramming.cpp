#include <iostream>
#include <vector>
#include <map>

using namespace std;

int numCallsWithDP = 0;
int numCallsWithoutDP = 0;

int longestIncreasingSequence(vector<int>& sequence, vector<int>& result)
{
    vector<vector<int>> longestSequence;
    int longestSeq = 0;

    for (int i = 0; i < sequence.size(); ++i)
    {
        int curLongest = 0;
        vector<int> curLongestSeq;

        for (int j = 0; j < i; ++j)
        {
            if (sequence[i] > sequence[j] && longestSequence[j].size() > curLongest)
            {
                curLongest = longestSequence[j].size();
                curLongestSeq = longestSequence[j];
            }
        }

        curLongestSeq.emplace_back(sequence[i]);
        longestSequence.emplace_back(curLongestSeq);

        if (longestSeq < longestSequence.size())
        {
            longestSeq = curLongestSeq.size();
            result = curLongestSeq;
        }
    }

    return longestSeq;
}

// Non-DP solution
/* int longestIncreasingSequence(vector<int>& sequence, int min, vector<int>& result)
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
} */

int longest_common_subsequence(const string& str1, const string& str2)
{
    map<pair<int, int>, string> commonSubs;

    for (int i = 0; i < str1.length(); ++i)
    {
        for (int j = 0; j < str2.length(); ++j)
        {
            if (str1[i] == str2[j])
            {
                string longest = "";
                if (i > 0 && j > 0)
                {
                    longest = commonSubs[pair<int, int>(i - 1, j -1)];
                }

                longest += str1[i];
                commonSubs.insert(pair<pair<int, int>, string>(pair<int, int>(i, j), longest));
            }
            else
            {
                string longest = "";
                if (i > 0)
                {
                    longest = commonSubs[pair<int, int>(i - 1, j)];
                }

                if (j > 0)
                {
                    string rightLongest = commonSubs[pair<int, int>(i, j - 1)];
                    if (rightLongest.length() > longest.length())
                    {
                        longest = rightLongest;
                    }
                }
                commonSubs.insert(pair<pair<int, int>, string>(pair<int, int>(i, j), longest));
            }
        }
    }

    string longest = commonSubs[pair<int, int>(str1.length() - 1, str2.length() - 1)];
    cout << longest.c_str() << endl;
    return longest.length();
}

int coin_change(const vector<int> coins, int n, int index, map<pair<int, int>, int>& vals)
{
    if (n == 0)
    {
        return 1;
    }

    if (n < 0)
    {
        return 0;
    }

    ++numCallsWithoutDP;

    if (vals.find(pair<int, int>(n, index)) != vals.end())
    {
        return vals[pair<int, int>(n, index)];
    }

    ++numCallsWithDP;
    int num = 0;
    for (int i = index; i < coins.size(); ++i)
    {
        int curVal = coin_change(coins, n - coins[i], i, vals);
        vals.insert(pair<pair<int, int>, int>(pair<int, int>(n - coins[i], i), curVal));
        num += curVal;
    }

    return num;
}

int coin_change(const vector<int> coins, int n)
{
    numCallsWithDP = 0;
    numCallsWithoutDP = 0;
    map<pair<int, int>, int> vals;
    return coin_change(coins, n, 0, vals);
}

int binomial_coefficient(int n, int k, map<pair<int, int>, int>& vals)
{
    if (n == k)
    {
        return 1;
    }

    if (n < k)
    {
        return 0;
    }

    if (n < 1)
    {
        return 0;
    }

    ++numCallsWithoutDP;

    if (vals.find(pair<int, int>(n, k)) != vals.end())
    {
        return vals[pair<int, int>(n, k)];
    }

    ++numCallsWithDP;

    int val1 = binomial_coefficient(n - 1, k, vals);
    vals.insert(pair<pair<int, int>, int>(pair<int, int>(n - 1, k), val1));

    int val2 = binomial_coefficient(n - 1, k - 1, vals);
    vals.insert(pair<pair<int, int>, int>(pair<int, int>(n - 1, k - 1), val2));

    return val1 + val2;
}

int binomial_coefficient(int n, int k)
{
    numCallsWithDP = 0;
    numCallsWithoutDP = 0;
    map<pair<int, int>, int> vals;
    return binomial_coefficient(n, k, vals);
}

int egg_drop(int egg, int floor, map<pair<int, int>, int>& vals)
{
    if (floor <= 0)
    {
        return 0;
    }

    if (floor == 1)
    {
        return 1;
    }

    if (egg == 1)
    {
        return floor;
    }

    ++numCallsWithoutDP;

    if (vals.find(pair<int, int>(egg, floor)) != vals.end())
    {
        return vals[pair<int, int>(egg, floor)];
    }

    ++numCallsWithDP;

    int minWorst = INT_MAX;
    for (int i = 1; i <= floor; ++i)
    {
        int minSuccess = egg_drop(egg, floor - i, vals);
        vals.insert(pair<pair<int, int>, int>(pair<int, int>(egg, floor - i), minSuccess));

        int minFail = egg_drop(egg - 1, i - 1, vals);
        vals.insert(pair<pair<int, int>, int>(pair<int, int>(egg - 1, i - 1), minFail));

        int minTries = minSuccess > minFail ? minSuccess + 1 : minFail + 1;        
        if (minTries < minWorst)
        {
            minWorst = minTries;
        }
    }


    vals.insert(pair<pair<int, int>, int>(pair<int, int>(egg, floor), minWorst));

    return minWorst;
}

int egg_drop(int egg, int floor)
{
    numCallsWithDP = 0;
    numCallsWithoutDP = 0;

    map<pair<int, int>, int> vals;
    return egg_drop(egg, floor, vals);
}

int longest_palindrome(const std::string& seq, int start, int end, map<pair<int, int>, int>& vals)
{
    if (start > end)
    {
        return 0;
    }

    if (start == end)
    {
        return 1;
    }

    ++numCallsWithoutDP;

    if (vals.find(pair<int, int>(start, end)) != vals.end())
    {
        return vals[pair<int, int>(start, end)];
    }

    ++numCallsWithDP;

    int longest = INT_MIN;
    if (seq[start] == seq[end])
    {
        longest = longest_palindrome(seq, start + 1, end - 1, vals) + 2;
    }
    else
    {
        int longestLeft = longest_palindrome(seq, start + 1, end, vals);
        vals.insert(pair<pair<int, int>, int>(pair<int, int>(start + 1, end), longestLeft));

        int longestRight = longest_palindrome(seq, start, end - 1, vals);
        vals.insert(pair<pair<int, int>, int>(pair<int, int>(start, end - 1), longestRight));

        longest = longestLeft > longestRight ? longestLeft : longestRight;
    }

    vals.insert(pair<pair<int, int>, int>(pair<int, int>(start, end), longest));
    return longest;
}

int longest_palindrome(const std::string& seq)
{
    map<pair<int, int>, int> vals;
    numCallsWithDP = 0;
    numCallsWithoutDP = 0;

    return longest_palindrome(seq, 0, seq.length() - 1, vals);
}

int cut_rod(const std::vector<int>& vals, int length, map<int, int>& arr)
{
    if (length == 0)
    {
        return 0;
    }

    ++numCallsWithoutDP;

    if (arr.find(length) != arr.end())
    {
        return arr[length];
    }

    ++numCallsWithDP;

    int maxVal = 0;
    for (int i = 1; i <= vals.size(); ++i)
    {
        if (i > length)
        {
            break;
        }

        int val = cut_rod(vals, length - i, arr);
        arr.insert(pair<int, int>(length - i, val));

        if (val + vals[i - 1] > maxVal)
        {
            maxVal = val + vals[i - 1];
        }
    }

    arr.insert(pair<int, int>(length, maxVal));

    return maxVal;
}

int cut_rod(const vector<int>& vals, int length)
{
    map<int, int> arr;
    numCallsWithDP = 0;
    numCallsWithoutDP = 0;

    return cut_rod(vals, length, arr);
}

int max_sum_increasing_subseq(const vector<int> arr)
{
    vector<int> max;
    max.resize(arr.size());

    int maxSum = 0;
    for (int i = 0; i < arr.size(); ++i)
    {
        int curMax = 0;
        for (int j = 0; j < i; ++j)
        {
            if (arr[j] < arr[i] && max[j] > curMax)
            {
                curMax = max[j];
            }
        }

        curMax += arr[i];
        max[i] = curMax;

        if (curMax > maxSum)
        {
            maxSum = curMax;
        }
    }

    return maxSum;
}

int longest_palindrome_subsequent(const string& str, int start, int end, vector<vector<int>>& vals)
{
    if (start > end)
    {
        return 0;
    }

    if (start == end)
    {
        return 1;
    }

    if (vals[start][end] != -1)
    {
        return vals[start][end];
    }

    if (str.at(start) == str.at(end))
    {
        return 2 + longest_palindrome_subsequent(str, start + 1, end - 1, vals);
    }

    int max = longest_palindrome_subsequent(str, start + 1, end, vals);
    int maxRight = longest_palindrome_subsequent(str, start, end - 1, vals);
    if (max < maxRight)
    {
        max = maxRight;
    }

    vals[start][end] = max;

    return max;
}

int longest_palindrome_subsequent(const string& str)
{
    vector<vector<int>> vals(str.length());
    for (int i = 0; i < str.length(); ++i)
    {
        vals[i].resize(str.length(), -1);
    }

    return longest_palindrome_subsequent(str, 0, str.length() - 1, vals);
}

// http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/
// int main()
int Longest_Increasing_Sequence()
{
    // vector<int> sequence = { 10, 3, 5, 2, 5, 7, 9, 1, 5, 2, 9, 4, 6, 2, 10};
    // vector<int> sequence = { 10, 9, 8, 5, 6, 3, 2, 4, 1, 2 };
    vector<int> sequence = { 10, 22, 9, 33, 21, 50, 41, 60, 80 };

    vector<int> result;

    // cout << longestIncreasingSequence(sequence, 0, result) << endl;
    cout << longestIncreasingSequence(sequence, result) << endl;
    cout << "numCallsWithDP: " << numCallsWithDP << endl;
    cout << "numCallsWithoutDP: " << numCallsWithoutDP << endl;
    for (int i = 0; i < result.size(); ++i)
    {
        cout << result[i] << " ";
    }

    int test;
    cin >> test;

    return 0;
}

// http://www.geeksforgeeks.org/dynamic-programming-set-4-longest-common-subsequence/
// int main()
int longest_common_subsequence()
{
    string str1 = "ABCDGH";
    string str2 = "AEDFHR";
    cout << longest_common_subsequence(str1, str2) << endl;

    str1 = "AGGTAB";
    str2 = "GXTXAYB";
    cout << longest_common_subsequence(str1, str2) << endl;

    int test;
    cin >> test;

    return 0;
}

// http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/
// int main()
int coin_change()
{
    vector<int> coins = { 1, 2, 3 };
    cout << coin_change(coins, 4) << endl;
    cout << "numCallsWithDP: " << numCallsWithDP << endl;
    cout << "numCallsWithoutDP: " << numCallsWithoutDP << endl;

    vector<int> coins2 = { 2, 5, 3, 6 };
    cout << coin_change(coins2, 10) << endl;
    cout << "numCallsWithDP: " << numCallsWithDP << endl;
    cout << "numCallsWithoutDP: " << numCallsWithoutDP << endl;

    int test;
    cin >> test;

    return 0;
}

// http://www.geeksforgeeks.org/dynamic-programming-set-9-binomial-coefficient/
// int main()
int binomial_coefficient()
{
    cout << binomial_coefficient(4, 2) << endl;
    cout << binomial_coefficient(5, 2) << endl;

    int test;
    cin >> test;

    return 0;
}

// http://www.geeksforgeeks.org/dynamic-programming-set-11-egg-dropping-puzzle/
// int main()
int egg_drop()
{
    cout << egg_drop(2, 10) << endl;
    cout << "numCallsWithDP: " << numCallsWithDP << endl;
    cout << "numCallsWithoutDP: " << numCallsWithoutDP << endl;

    int test;
    cin >> test;

    return 0;
}

// TODO this
// http://www.geeksforgeeks.org/dynamic-programming-set-10-0-1-knapsack-problem/
// int main()
int knapsack()
{
    // TODO this
    vector<int> vals = { 60, 100, 120 };
    vector<int> weights = { 10, 20, 30 }; 

    cout << "numCallsWithDP: " << numCallsWithDP << endl;
    cout << "numCallsWithoutDP: " << numCallsWithoutDP << endl;

    int test;
    cin >> test;

    return 0;
}

// http://www.geeksforgeeks.org/dynamic-programming-set-12-longest-palindromic-subsequence/
// int main()
int longest_palindrome()
{
    string seq = "GEEKSFORGEEKS";
    cout << longest_palindrome(seq) << endl;
    cout << "numCallsWithDP: " << numCallsWithDP << endl;
    cout << "numCallsWithoutDP: " << numCallsWithoutDP << endl;

    seq = "BBABCBCAB";
    cout << longest_palindrome(seq) << endl;
    cout << "numCallsWithDP: " << numCallsWithDP << endl;
    cout << "numCallsWithoutDP: " << numCallsWithoutDP << endl;

    int test;
    cin >> test;

    return 0;
}

// http://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/
// int main()
int cut_rod()
{
    vector<int> arr = { 1, 5, 8, 9, 10, 17, 17, 20 };
    cout << cut_rod(arr, arr.size()) << endl;
    cout << "numCallsWithDP: " << numCallsWithDP << endl;
    cout << "numCallsWithoutDP: " << numCallsWithoutDP << endl;

    int test;
    cin >> test;

    return 0;
}

// http://www.geeksforgeeks.org/dynamic-programming-set-14-maximum-sum-increasing-subsequence/
// int main()
int max_sum_increasing_subseq()
{
    vector<int> arr = { 1, 101, 2, 3, 100, 4, 5 };
    cout << max_sum_increasing_subseq(arr) << endl;

    vector<int> arr2 = { 3, 4, 5, 10 };
    cout << max_sum_increasing_subseq(arr2) << endl;

    int test;
    cin >> test;

    return 0;
}

// http://www.geeksforgeeks.org/dynamic-programming-set-12-longest-palindromic-subsequence/
// int main()
int longest_palindrome_subsequent()
{
    string str = "BBABCBCAB";
    cout << longest_palindrome_subsequent(str) << endl;

    string str2 = "GEEKS FOR GEEKS";
    cout << longest_palindrome_subsequent(str2) << endl;

    int test;
    cin >> test;

    return 0;
}