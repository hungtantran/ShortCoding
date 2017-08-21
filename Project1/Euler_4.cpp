// A palindromic number reads the same both ways.The largest palindrome made from the product of two 2 - digit numbers is 9009 = 91 × 99.
// Find the largest palindrome made from the product of two 3 - digit numbers.
#include <iostream>

using namespace std;

string numToString(int num) {
    string numStr;
    while (num > 0) {
        numStr = numStr.append(string(1, '0' + num % 10));
        num /= 10;
    }
    return numStr;
}

bool isPalindrome(string num) {
    for (int i = 0; i < num.length() / 2; ++i) {
        if (num.at(i) != num.at(num.length() - 1 - i)) {
            return false;
        }
    }
    return true;
}

// int main() {
int euler_4() {
    int maxI = INT_MIN, maxJ = INT_MIN, max = INT_MIN;
    for (int i = 999; i >= 100; i--) {
        for (int j = i; j >= 100; j--) {
            if (i < maxI && j < maxJ) {
                break;
            }
            int num = i * j;
            string numStr = numToString(num);
            if (isPalindrome(numStr) && num > max) {
                max = num;
                maxI = i;
                maxJ = j;
            }
        }
    }
    cout << "Max = " << max << ", i = " << maxI << ", j = " << maxJ << endl;
    return 0;
}