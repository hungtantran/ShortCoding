#include <iostream>
#include <map>
#include <vector>
#include "HelperMethod.h"

using namespace std;

vector<int> LongestCommonSubsequence(vector<int>& left, vector<int>& right) {
    if (left.size() == 0 || right.size() == 0) {
        return vector<int>();
    }

    vector<int> new_left(left.begin() + 1, left.end());
    vector<int> new_right(right.begin() + 1, right.end());
    if (left.at(0) == right.at(0)) {
        vector<int> result = { left.at(0 )};
        vector<int> lcs = LongestCommonSubsequence(new_left, new_right);
        result.insert(result.end(), lcs.begin(), lcs.end());
        return result;
    }

    vector<int> lcs_left = LongestCommonSubsequence(new_left, right);
    vector<int> lcs_right = LongestCommonSubsequence(left, new_right);
    if (lcs_left.size() > lcs_right.size()) {
        return lcs_left;
    }
    return lcs_right;
}

int main() {
    vector<int> left = { 1, 2, 3, 4, 1 };
    vector<int> right = { 3, 4, 1, 2, 1, 3 };
    vector<int> lcs = LongestCommonSubsequence(left, right);
    HelperMethod::printArray(lcs);
    return 0;
}