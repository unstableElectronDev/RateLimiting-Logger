// Basic counter bucket Rate Limiter Implementation in C++

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Logger {
    
private:
    unordered_map<string, int> firstOccurrence;
    unordered_map<string, int> count;    
    int timewindow = 10;
    int rate = 2;
    
public: 
    bool RateLimiter(int timestamp, string message) {
        if (firstOccurrence.find(message) == firstOccurrence.end() || (timestamp - firstOccurrence[message]) >= timewindow) {
            firstOccurrence[message] = timestamp;
            count[message] = 1;
            return true;
        }
        if (count[message] < rate) {
            count[message]++;
            return true;
        }
        return false;
    }
    
    void printMessage(bool shouldPrint, string message) {
        if(shouldPrint) {
            cout<<message<<endl;
        } else {
            cout<<"Rate limit exceeded"<<endl;
        }
    }
}; 


int main()
{
    Logger l;
    l.printMessage(l.RateLimiter(1, "foo"), "foo");
    l.printMessage(l.RateLimiter(1, "foo"), "foo");
    l.printMessage(l.RateLimiter(2, "bar"), "bar");
    l.printMessage(l.RateLimiter(3, "foo"), "foo");
    l.printMessage(l.RateLimiter(8, "bar"), "bar");
    l.printMessage(l.RateLimiter(10, "foo"), "foo");
    l.printMessage(l.RateLimiter(11, "foo"), "foo");
    
    return 0;
}


// Output:
// foo
// foo
// bar
// Rate limit exceeded
// bar
// Rate limit exceeded
// foo
