// The prime factors of 13195 are 5, 7, 13 and 29.
// What is the largest prime factor of the number 600851475143 ?

#include <iostream>

using namespace std;

bool isPrimeEuler(unsigned long long num) {
    for (unsigned long long i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    cout << num << endl;
    return true;
}

// int main() {
int euler_3() {
    const unsigned long long num = 600851475143;
    const unsigned long long max = sqrt(num);
    for (unsigned long long i = max; i >= 2; --i) {
        if (num % i == 0 && isPrimeEuler(i)) {
            cout << "Largest prime " << i << endl;
            break;
        }
    }
    return 0;
}