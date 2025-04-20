#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class BigInt {
    vector<int> digits;

public:
    BigInt() {}
    BigInt(unsigned long long n) {
        if (n == 0) digits.push_back(0);
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
    }

    BigInt& operator*=(int x) {
        int carry = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            int prod = digits[i] * x + carry;
            digits[i] = prod % 10;
            carry = prod / 10;
        }
        while (carry > 0) {
            digits.push_back(carry % 10);
            carry /= 10;
        }
        return *this;
    }

    BigInt operator*(int x) const {
        BigInt result = *this;
        result *= x;
        return result;
    }

    BigInt& operator*=(const BigInt& other) {
        vector<int> result(digits.size() + other.digits.size(), 0);
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                int val = result[i + j] + digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result[i + j] = val % 10;
                carry = val / 10;
            }
        }
        while (!result.empty() && result.back() == 0)
            result.pop_back();
        if (result.empty()) result.push_back(0);
        digits = result;
        return *this;
    }

    BigInt operator*(const BigInt& other) const {
        BigInt result = *this;
        result *= other;
        return result;
    }

    BigInt& operator/=(int x) {
        int remainder = 0;
        for (int i = digits.size() - 1; i >= 0; --i) {
            int current = remainder * 10 + digits[i];
            digits[i] = current / x;
            remainder = current % x;
        }
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        return *this;
    }

    friend ostream& operator<<(ostream& os, const BigInt& num) {
        for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it)
            os << *it;
        return os;
    }
};

BigInt comb(int n, int k) {
    if (k < 0 || k > n) return BigInt(0);
    k = min(k, n - k);
    BigInt res(1);
    for (int i = 1; i <= k; ++i) {
        res *= (n - k + i);
        res /= i;
    }
    return res;
}

int main() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<string> parts;
    string part;
    while (iss >> part) parts.push_back(part);
    int N = stoi(parts[0]);
    vector<string> games(parts.begin() + 1, parts.begin() + 1 + N);

    BigInt total(1);
    for (int i = 0; i < N; ++i) {
        string game = games[i];
        int a, b; char colon;
        istringstream(game) >> a >> colon >> b;

        bool is_fifth = (i == 4) && (N == 5);
        int win = max(a, b), lose = min(a, b);
        BigInt ways(1);

        if (is_fifth) {
            if (win == 15 && lose <= 13) {
                ways = comb(14 + lose, lose);
            } else {
                int m = (win + lose - 28) / 2;
                ways = comb(28, 14);
                if (m > 0) {
                    BigInt pow2(1);
                    for (int j = 0; j < m - 1; ++j) pow2 *= 2;
                    ways *= pow2;
                }
            }
        } else {
            if (win == 25 && lose <= 23) {
                ways = comb(24 + lose, lose);
            } else {
                int m = (win + lose - 48) / 2;
                ways = comb(48, 24);
                if (m > 0) {
                    BigInt pow2(1);
                    for (int j = 0; j < m - 1; ++j) pow2 *= 2;
                    ways *= pow2;
                }
            }
        }
        total *= ways;
    }
    cout << total << endl;
    return 0;
}