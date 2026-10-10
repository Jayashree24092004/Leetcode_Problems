
long long minSumSquareDiff(int* nums1, int nums1Size,
                           int* nums2, int nums2Size,
                           int k1, int k2) {
    long long k = (long long)k1 + k2;
    int low = 0, high = 0;

    for (int i = 0; i < nums1Size; i++) {
        int d = abs(nums1[i] - nums2[i]);
        if (d > high)
            high = d;
    }

    while (low < high) {
        int mid = low + (high - low) / 2;
        long long needed = 0;

        for (int i = 0; i < nums1Size; i++) {
            int d = abs(nums1[i] - nums2[i]);

            if (d > mid)
                needed += d - mid;
        }

        if (needed <= k)
            high = mid;
        else
            low = mid + 1;
    }

    int level = low;
    long long used = 0;
    long long result = 0;

    for (int i = 0; i < nums1Size; i++) {
        int d = abs(nums1[i] - nums2[i]);

        if (d > level) {
            used += d - level;
            d = level;
        }

        result += (long long)d * d;
    }

    long long remaining = k - used;

    if (level > 0)
        result -= remaining * (2LL * level - 1);

    return result;
}
