#include <iostream>
#include <map>

using namespace std;

map<pair<int, int>, tuple<int, int, int, bool>> mem;

bool LongestPlaindromicRecurse(string str, int start, int end, int* max_start, int* max_end, int* max) {
    if (start == end) {
        *max_start = start;
        *max_end = end;
        *max = 1;
        return true;
    }
    
    if (end - start == 1 && str.at(start) == str.at(end)) {
        *max_start = start;
        *max_end = end;
        *max = 2;
        return true;
    }

    const auto& val = mem.find(make_pair(start, end));
    if (val != mem.end()) {
        *max_start = std::get<0>(val->second);
        *max_end = std::get<1>(val->second);
        *max = std::get<2>(val->second);
        return std::get<3>(val->second);
    }

    if (str.at(start) == str.at(end)) {
        int new_max = 0;
        int new_max_start = 0;
        int new_max_end = 0;
        if (LongestPlaindromicRecurse(str, start + 1, end - 1, &new_max_start, &new_max_end, &new_max)) {
            *max_start = start;
            *max_end = end;
            *max = new_max + 2;
            mem.insert(make_pair(make_pair(start, end), make_tuple(start, end, new_max + 2, true)));
            return true;
        }
    }

    int max_left = 0, max_start_left = 0, max_end_left = 0;
    int max_right = 0, max_start_right = 0, max_end_right = 0;
    LongestPlaindromicRecurse(str, start + 1, end, &max_start_left, &max_end_left, &max_left);
    LongestPlaindromicRecurse(str, start, end - 1, &max_start_right, &max_end_right, &max_right);
    if (max_left > max_right) {
        *max = max_left;
        *max_start = max_start_left;
        *max_end = max_end_left;
    } else {
        *max = max_right;
        *max_start = max_start_right;
        *max_end = max_end_right;
    }

    mem.insert(make_pair(make_pair(start, end), make_tuple(*max_start, *max_end, *max, false)));

    return false;
}

string LongestPalindromicSubstring(string str) {
    if (str.length() == 0){
        return str;
    }

    int max, max_start, max_end;
    mem.clear();
    LongestPlaindromicRecurse(str, 0, str.length() - 1, &max_start, &max_end, &max);
    return str.substr(max_start, max_end - max_start + 1);
}

//int main() {
int LongestPalindromicSubstring() {
    cout << LongestPalindromicSubstring("bananas").c_str() << endl;
    cout << LongestPalindromicSubstring("a").c_str() << endl;
    cout << LongestPalindromicSubstring("abccba").c_str() << endl;
    cout << LongestPalindromicSubstring("aaaaaa").c_str() << endl;
    cout << LongestPalindromicSubstring("").c_str() << endl;

    return 0;
}