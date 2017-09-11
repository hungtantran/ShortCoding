// http://practice.geeksforgeeks.org/problems/sum-palindrome/0

#include <iostream>

using namespace std;

int reverse(int num) {
    int reverse = 0;
    while (num > 0) {
        int divider = num % 10;
        reverse = reverse * 10 + divider;
        num /= 10;
    }
    return reverse;
}

//int main() {
int ReverseNumber() {
    cout << reverse(10) << endl;
    cout << reverse(55) << endl;
    cout << reverse(102030) << endl;
    return 0;
}