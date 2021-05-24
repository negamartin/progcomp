#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int modulo[3] = {0, 0, 0};
    long long count = 0;
    while (true) {
        char c;
        if (!(cin >> c)) {
            break;
        }
        int num = ((int)c) - '0';
        if (num < 0 || num >= 10) {
            rep(i, 3) { modulo[i] = 0; }
            continue;
        }
        num %= 3;
        rotate(&modulo[0], &modulo[(3 - num) % 3], &modulo[3]);
        modulo[num] += 1;
        count += modulo[0];
    }
    cout << count << '\n';
}
