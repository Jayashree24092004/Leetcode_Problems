#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int l, r, w;
    int idx;
} Interval;

/* Sort by ending point */
int cmpInterval(const void *a, const void *b) {
    Interval *x = (Interval *)a;
    Interval *y = (Interval *)b;

    if (x->r != y->r)
        return x->r < y->r ? -1 : 1;

    return x->idx - y->idx;
}

/* 
   Returns the last interval whose right endpoint
   is strictly smaller than 'left'.
*/
int findPrev(Interval *arr, int n, int left) {
    int lo = 0, hi = n - 1;
    int ans = -1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (arr[mid].r < left) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return ans;
}

/*
   Compare two arrays lexicographically.
   Returns:
      < 0 if a < b
      > 0 if a > b
       0 if equal
*/
int lexCompare(int *a, int lenA, int *b, int lenB) {
    int len = lenA < lenB ? lenA : lenB;

    for (int i = 0; i < len; i++) {
        if (a[i] != b[i])
            return a[i] < b[i] ? -1 : 1;
    }

    if (lenA == lenB)
        return 0;

    return lenA < lenB ? -1 : 1;
}

/*
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumWeight(int** intervals, int intervalsSize,
                   int* intervalsColSize, int* returnSize) {

    int n = intervalsSize;

    Interval *arr = malloc(sizeof(Interval) * n);

    for (int i = 0; i < n; i++) {
        arr[i].l = intervals[i][0];
        arr[i].r = intervals[i][1];
        arr[i].w = intervals[i][2];
        arr[i].idx = i;
    }

    /* Sort intervals by right endpoint */
    qsort(arr, n, sizeof(Interval), cmpInterval);

    /*
       dp[i][k] = maximum score using first i intervals
                  and choosing exactly k intervals.

       path[i][k] = corresponding original indices.
    */
    ll *dp = calloc((n + 1) * 5, sizeof(ll));
    int *len = calloc((n + 1) * 5, sizeof(int));

    /*
       path has:
       (n + 1) * 5 states,
       each containing at most 4 indices.
    */
    int *path = calloc((n + 1) * 5 * 4, sizeof(int));

    #define DP(i,k) dp[(i) * 5 + (k)]
    #define LEN(i,k) len[(i) * 5 + (k)]
    #define PATH(i,k) (&path[((i) * 5 + (k)) * 4])

    /*
       Mark impossible exact-k states.
    */
    for (int i = 0; i <= n; i++) {
        for (int k = 1; k <= 4; k++) {
            DP(i, k) = -1;
        }
    }

    /* 0 intervals gives score 0 */
    for (int i = 0; i <= n; i++) {
        DP(i, 0) = 0;
        LEN(i, 0) = 0;
    }

    for (int i = 1; i <= n; i++) {

        Interval cur = arr[i - 1];

        /*
           Option 1:
           Don't take current interval.
        */
        for (int k = 0; k <= 4; k++) {
            DP(i, k) = DP(i - 1, k);
            LEN(i, k) = LEN(i - 1, k);

            memcpy(PATH(i, k),
                   PATH(i - 1, k),
                   sizeof(int) * 4);
        }

        /*
           Find previous compatible interval.

           p = number of intervals before current that have
               right endpoint < current.left.

           DP[p][k-1] represents using those intervals.
        */
        int prev = findPrev(arr, n, cur.l);
        int p = prev + 1;

        for (int k = 1; k <= 4; k++) {

            if (DP(p, k - 1) == -1)
                continue;

            ll newScore = DP(p, k - 1) + cur.w;

            int newLen = LEN(p, k - 1) + 1;

            int candidate[4];

            /*
               Copy previous selected indices.
            */
            for (int j = 0; j < LEN(p, k - 1); j++)
                candidate[j] = PATH(p, k - 1)[j];

            /*
               Insert current original index so that
               the resulting array stays sorted.
            */
            int pos = newLen - 1;

            while (pos > 0 && candidate[pos - 1] > cur.idx) {
                candidate[pos] = candidate[pos - 1];
                pos--;
            }

            candidate[pos] = cur.idx;

            /*
               Decide whether taking current interval is better.
            */
            int take = 0;

            if (newScore > DP(i, k)) {
                take = 1;
            }
            else if (newScore == DP(i, k)) {

                if (lexCompare(candidate, newLen,
                               PATH(i, k), LEN(i, k)) < 0) {
                    take = 1;
                }
            }

            if (take) {
                DP(i, k) = newScore;
                LEN(i, k) = newLen;

                for (int j = 0; j < newLen; j++)
                    PATH(i, k)[j] = candidate[j];
            }
        }
    }

    /*
       We can choose AT MOST 4 intervals.
       Find the best among 0,1,2,3,4.
    */
    int bestK = 0;

    for (int k = 1; k <= 4; k++) {

        if (DP(n, k) > DP(n, bestK)) {
            bestK = k;
        }
        else if (DP(n, k) == DP(n, bestK)) {

            if (lexCompare(PATH(n, k), LEN(n, k),
                           PATH(n, bestK), LEN(n, bestK)) < 0) {
                bestK = k;
            }
        }
    }

    *returnSize = LEN(n, bestK);

    int *result = malloc(sizeof(int) * (*returnSize));

    for (int i = 0; i < *returnSize; i++)
        result[i] = PATH(n, bestK)[i];

    free(arr);
    free(dp);
    free(len);
    free(path);

    return result;
}