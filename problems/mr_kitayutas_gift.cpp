#include <bits/stdc++.h>

using namespace std;

bool is_palindrome(string s) {
    int p1=0, p2=s.size()-1;
    while (p1 < p2) {
        if (s[p1] != s[p2]) return false;
        p1++; p2--;
    }
    return true;
}

int main() {

    string s;
    cin >> s;

    string pref="", suf=s;

    for (int j=0; j<26; j++) {
        string t = pref + string(1, (char)('a'+j)) + suf;
        if (is_palindrome(t)) {
            cout << t << endl;
            return 0;
        }
    }

    for (int i=0; i < s.size(); i++) {
        pref+=s[i];
        suf.erase(0, 1);
        for (int j=0; j<26; j++) {
            string t = pref + string(1, (char)('a'+j)) + suf;
            if (is_palindrome(t)) {
                cout << t << endl;
                return 0;
            }
        }
    }
    cout << "NA" << endl;
    return 0;

}