#include <bits/stdc++.h>
//Only cout functionality available
//So read input in standard data types and then convert them to u128 type
using namespace std;
using ll = long long;

typedef __uint128_t u128;

namespace another {
    std::string to_string(__int128 val) {
        bool neg = false;
        if (val < 0) neg = true, val = -val;
        auto high = ll(val / (__int128)1e18L);
        auto low = ll(val - (__int128)1e18L * high);
        std::string res;
        if (neg) res += '-';
        if (high > 0) {
            res += std::to_string(high);
            std::string temp = std::to_string(low);
            res += std::string(18u-temp.size(),'0');
            res += temp;
        } else {
            res += std::to_string(low);
        }
        return res;
    }
}

int main() {
    
    //Printing factorial 30
    u128 ans = 1;
    for (u128 i = 1; i <= 30; ++i) {
        ans = ans * i;
    }
    cout << another::to_string(ans);
    return 0;
}