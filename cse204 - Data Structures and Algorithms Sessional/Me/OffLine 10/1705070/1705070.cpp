#include <bits/stdc++.h>

#define MAX 50
using namespace std;
int dp[MAX][MAX];

vector<string> findLCS(string s1, string s2, int m, int n) {
    if (m == 0 || n == 0) {
        vector<string> v(1);
        return v;
    }
    if (s1[m - 1] == s2[n - 1]) {
        vector<string> lcs = findLCS(s1, s2, m - 1, n - 1);
        for (auto &ch:lcs) {
            ch.push_back(s1[m - 1]);
        }
        return lcs;
    }
    if (dp[m - 1][n] > dp[m][n - 1]) {
        return findLCS(s1, s2, m - 1, n);
    }
    if (dp[m][n - 1] > dp[m - 1][n]) {
        return findLCS(s1, s2, m, n - 1);
    }
    vector<string> top = findLCS(s1, s2, m - 1, n);
    vector<string> left = findLCS(s1, s2, m, n - 1);

    top.insert(top.end(), left.begin(), left.end());
    return top;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s1, s2;
    cout << "------------------------" << endl;
    cout << "Enter two string" << endl;
    cin >> s1 >> s2;

    int length_1 = s1.length();
    int length_2 = s2.length();
    
    for (int i = 1; i <= length_1; i++) {
        for (int j = 1; j <= length_2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    vector<string> v = findLCS(s1, s2, length_1, length_2);
    set<string> allLCS;
    for (auto &i:v) {
        allLCS.insert(i);
    }
    for (auto &i : allLCS) {
        cout << i << endl;
    }

    cout << "------------------------" << endl;
    return EXIT_SUCCESS;
}



