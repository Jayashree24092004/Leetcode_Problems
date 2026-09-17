int minSumOfLengths(int* arr, int arrSize, int target) {
    int minLen[arrSize];
    
    // Initialize: no valid subarray found yet
    for (int i = 0; i < arrSize; i++) {
        minLen[i] = 1000000;
    }

    int left = 0;
    int sum = 0;
    int ans = 1000000;

    for (int right = 0; right < arrSize; right++) {
        sum += arr[right];

        while (sum > target) {
            sum -= arr[left];
            left++;
        }

        if (sum == target) {
            int len = right - left + 1;

            // Check if there was a previous non-overlapping subarray
            if (left > 0 && minLen[left - 1] != 1000000) {
                int total = len + minLen[left - 1];

                if (total < ans) {
                    ans = total;
                }
            }

            // Store shortest subarray ending at or before right
            if (right == 0 || len < minLen[right - 1]) {
                minLen[right] = len;
            } else {
                minLen[right] = minLen[right - 1];
            }
        } else {
            if (right > 0)
                minLen[right] = minLen[right - 1];
        }
    }

    if (ans == 1000000)
        return -1;

    return ans;
}