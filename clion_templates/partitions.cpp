const int N = 1000;
const int M = 2e5 + 5;
vector<int> pentagonal;
vector<mod_int> partitions;
void calcPartitions() {
    int cur = 1;
    pentagonal.resize(N + 1);
    for (int i = 1; i <= N; ++i) {
        pentagonal[i] = cur * (3 * cur - 1) / 2;
        if (cur > 0) cur = -cur;
        else cur = -cur + 1;
    }
    partitions.resize(M + 1);
    partitions[0] = 1;
    cur = 0;
    for (int i = 1; i <= M; ++i) {
        while (cur + 1 <= M && pentagonal[cur + 1] <= i) {
            ++cur;
        }
        int tcur = 1, sign = 1;
        while (tcur <= cur) {
            partitions[i] += (sign > 0 ? 1: -1) * partitions[i - pentagonal[tcur]];
            tcur++;
            if (sign == 1) sign++;
            else if (sign == 2) sign = -1;
            else if (sign == -1) sign = -2;
            else sign = 1;
        }
    }
}