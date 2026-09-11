int totalNumbers(int* digits, int digitsSize) {
    int count = 0;

    for (int num = 100; num <= 999; num++) {
        // Number must be even
        if (num % 2 != 0)
            continue;

        int freq[10] = {0};

        // Count available digits
        for (int i = 0; i < digitsSize; i++)
            freq[digits[i]]++;

        int n = num;
        int valid = 1;

        // Check the 3 digits
        for (int i = 0; i < 3; i++) {
            int d = n % 10;
            n /= 10;

            if (freq[d] == 0) {
                valid = 0;
                break;
            }

            freq[d]--;
        }

        if (valid)
            count++;
    }

    return count;
}