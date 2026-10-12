int maxSum(int* nums, int numsSize, int k) {
    long long MOD = 1000000007;
    int count[31] = {0};

    for (int i = 0; i < numsSize; i++) {
        for (int b = 0; b < 31; b++) {
            if (nums[i] & (1 << b)) {
                count[b]++;
            }
        }
    }

    long long ans = 0;

    for (int i = 0; i < k; i++) {
        long long num = 0;

        for (int b = 30; b >= 0; b--) {
            if (count[b] > 0) {
                num |= (1LL << b);
                count[b]--;
            }
        }

        ans = (ans + num * num) % MOD;
    }

    return (int)ans;
}