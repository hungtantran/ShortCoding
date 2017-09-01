#include <iostream>
#include <thread>
#include "future"

using namespace std;

int HelloWorld(const string& message, int result) {
    this_thread::sleep_for(chrono::seconds(2));
    cout << message.c_str() << endl;
    return result;
}

void test() {
    future<int> hello = std::async(launch::async, HelloWorld, "Future done", 6);
    //int result = hello.get();
    //cout << result << endl;
}

int SimpleAsync() {
//int main() {
    cout << "test starts" << endl;
    test();
    cout << "test ends" << endl;
    this_thread::sleep_for(chrono::seconds(4));
    return 0;
}