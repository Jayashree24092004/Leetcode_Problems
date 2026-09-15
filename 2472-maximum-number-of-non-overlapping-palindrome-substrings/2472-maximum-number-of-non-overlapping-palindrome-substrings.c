#include <stdlib.h>
#include <string.h>

int maxPalindromes(char* s, int k) {

    int n = strlen(s);

    // pal[i][j] = 1 if s[i...j] is a palindrome
    char **pal = malloc(n * sizeof(char *));

    for (int i = 0; i < n; i++) {
        pal[i] = calloc(n, sizeof(char));
    }

    // Every single character is a palindrome
    for (int i = 0; i < n; i++) {
        pal[i][i] = 1;
    }

    // Check substrings of length 2 or more
    for (int len = 2; len <= n; len++) {

        for (int i = 0; i + len <= n; i++) {

            int j = i + len - 1;

            if (s[i] == s[j]) {

                if (len == 2 || pal[i + 1][j - 1]) {
                    pal[i][j] = 1;
                }
            }
        }
    }

    // dp[i] = maximum palindromes using first i characters
    int *dp = calloc(n + 1, sizeof(int));

    for (int end = 0; end < n; end++) {

        // Don't select a palindrome ending here
        dp[end + 1] = dp[end];

        for (int start = 0; start <= end; start++) {

            int len = end - start + 1;

            if (len >= k && pal[start][end]) {

                if (dp[start] + 1 > dp[end + 1]) {
                    dp[end + 1] = dp[start] + 1;
                }
            }
        }
    }

    int answer = dp[n];

    // Free memory
    for (int i = 0; i < n; i++) {
        free(pal[i]);
    }

    free(pal);
    free(dp);

    return answer;
}