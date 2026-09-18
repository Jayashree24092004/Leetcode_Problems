/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** maxNumOfSubstrings(char* s, int* returnSize) {
    int n = strlen(s);

    int first[26];
    int last[26];

    // Initialize
    for (int i = 0; i < 26; i++) {
        first[i] = n;
        last[i] = -1;
    }

    // Find first and last occurrence of every character
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';

        if (first[c] == n)
            first[c] = i;

        last[c] = i;
    }

    // Store valid intervals [start, end]
    int starts[26];
    int ends[26];
    int count = 0;

    // Try to create the smallest valid substring for each character
    for (int c = 0; c < 26; c++) {

        if (first[c] == n)
            continue;

        int start = first[c];
        int end = last[c];
        int valid = 1;

        for (int i = start; i <= end; i++) {
            int x = s[i] - 'a';

            // This character occurs before our start,
            // so substring cannot contain all its occurrences.
            if (first[x] < start) {
                valid = 0;
                break;
            }

            // We must include all occurrences of this character.
            if (last[x] > end)
                end = last[x];
        }

        if (valid) {
            starts[count] = start;
            ends[count] = end;
            count++;
        }
    }

    /*
     * Greedy:
     * Sort intervals by ending position.
     *
     * Since there are only 26 lowercase letters,
     * we can simply repeatedly select the interval
     * with the smallest end.
     */

    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (ends[j] < ends[i]) {
                int temp = starts[i];
                starts[i] = starts[j];
                starts[j] = temp;

                temp = ends[i];
                ends[i] = ends[j];
                ends[j] = temp;
            }
        }
    }

    // At most 26 substrings
    char** result = malloc(sizeof(char*) * count);

    int prevEnd = -1;
    *returnSize = 0;

    for (int i = 0; i < count; i++) {

        if (starts[i] > prevEnd) {

            int len = ends[i] - starts[i] + 1;

            result[*returnSize] = malloc(sizeof(char) * (len + 1));

            strncpy(
                result[*returnSize],
                s + starts[i],
                len
            );

            result[*returnSize][len] = '\0';

            prevEnd = ends[i];
            (*returnSize)++;
        }
    }

    return result;
}