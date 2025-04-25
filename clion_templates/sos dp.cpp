const int MLOG = 20;
const int MAXN = 1 << MLOG;

void forward1(vector<mod_int> &dp) {
    for (int i = 0; i < MLOG; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            if (j & (1 << i))
                dp[j] += dp[j ^ (1 << i)];
        }
    }
}

void forward2(vector<mod_int> &dp) {
    for (int i = 0; i < MLOG; ++i) {
        for (int j = MAXN - 1; j >= 0; --j) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] += dp[j];
        }
    }
}

void backward1(vector<mod_int> &dp) {
    for (int i = 0; i < MLOG; ++i) {
        for (int j = MAXN - 1; j >= 0; --j) {
            if (j & (1 << i))
                dp[j] -= dp[j ^ (1 << i)];
        }
    }
}

void backward2(vector<mod_int> &dp) {
    for (int i = 0; i < MLOG; ++i) {
        for (int j = 0; j < MAXN ; ++j) {
            if (j & (1 << i))
                dp[j ^ (1 << i)] -= dp[j];
        }
    }
}