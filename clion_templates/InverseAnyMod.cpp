int64_t euclid_invert(int64_t a, int64_t mod){
    a %= mod;
    int64_t b = mod, x = 0, x2 = 1, y = 1, y2 = 0, tmp;
    while(b){
        int64_t q = a / b, r = a % b;
        tmp = x;
        x = x2 - q * x;
        x2 = tmp;
        tmp = y;
        y = y2 - q * y;
        y2 = tmp;
        a = b; b = r;
    }
    if(x2 < 0) x2 += mod;
    return x2;
}