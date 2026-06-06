//Sliding Window Rate Limiter Implementation in C++


#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
using namespace std;

class Logger {
private:
    int windowSize;
    int maxRequests;
    unordered_map<string, deque<int>> messageWindows;

public:
    Logger(int windowSize, int maxRequests)
        : windowSize(windowSize), maxRequests(maxRequests) {}

    bool RateLimiter(int timestamp, const string& message) {
        deque<int>& window = messageWindows[message];

        while (!window.empty() && (timestamp - window.front()) >= windowSize) {
            window.pop_front();
        }

        if ((int)window.size() < maxRequests) {
            window.push_back(timestamp);
            return true;
        }
        return false;
    }

    void printMessage(bool shouldPrint, const string& message) {
        if (shouldPrint) {
            cout << message << endl;
        } else {
            cout << "[" << message << "] Rate limit exceeded" << endl;
        }
    }
};

int main() {
    Logger l(5, 2);

    l.printMessage(l.RateLimiter(1, "foo"), "foo");
    l.printMessage(l.RateLimiter(2, "foo"), "foo");
    l.printMessage(l.RateLimiter(2, "bar"), "bar");
    l.printMessage(l.RateLimiter(3, "foo"), "foo");
    l.printMessage(l.RateLimiter(6, "foo"), "foo");
    l.printMessage(l.RateLimiter(6, "foo"), "foo");

    return 0;
}

// output:
// foo
// foo
// bar
// [foo] Rate limit exceeded
// foo
// [foo] Rate limit exceeded