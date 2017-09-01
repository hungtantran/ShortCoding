#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <queue>

using namespace std;

struct SharedQueue {
    SharedQueue() {}
    virtual ~SharedQueue() {};

    int pop() {
        int num = 0;
        {
            unique_lock<mutex> ul(lock_);
            while (nums_.empty()) {
                cv_.wait(ul);
            }
            num = nums_.front();
            nums_.pop();
        }
        return num;
    }

    void push(int num) {
        lock_guard<mutex> guard(lock_);
        nums_.push(num);
        cv_.notify_all();
    }

    mutex lock_;
    condition_variable cv_;
    queue<int> nums_;
};

void Consumer(SharedQueue* queue, int* sum) {
    for (int i = 0; i < 10; ++i) {
        *sum += queue->pop();
    }
}

void Producer(SharedQueue* queue, int num) {
    for (int i = 1; i <= num; ++i) {
        queue->push(i);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

// int ConsumerProducer() {
int main() {
    SharedQueue queue;
    int sum = 0;
    //vector<future<void>> consumers(10, std::move(async(launch::async, Consumer, &queue, &sum)));
    vector<future<void>> consumers;
    for (int i = 0; i < 10; ++i) {
        consumers.push_back(std::move(async(launch::async, Consumer, &queue, &sum)));
    }
    future<void> producer = async(launch::async, Producer, &queue, 100);
    producer.wait();
    for (auto& consumer : consumers) {
        consumer.wait();
    }
    cout << "Sum = " << sum << endl;
    return 0;
}