#include <iostream>
#include <string>
using namespace std;

void String23(string s0, int len, string current = "") {
    if (current.size() == len) {
        cout << current << endl;
        return;
    }
    
    for (char c : s0) {
        String23(s0, len, current + c);
    }
}

int main() {
    string s0;
    cin >> s0;
    
    // Generate strings of length 1 and 2
    for (int len = 1; len <= 2; len++) {
        String23(s0, len);
    }
    return 0;
} 