int largestOverlap(int** img1, int img1Size, int* img1ColSize,
                   int** img2, int img2Size, int* img2ColSize) {
    
    int n = img1Size;
    int maxOverlap = 0;

    // Shift img1 by (dr, dc)
    for (int dr = -(n - 1); dr <= n - 1; dr++) {
        for (int dc = -(n - 1); dc <= n - 1; dc++) {

            int overlap = 0;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    // Position in img1 after shifting
                    int ni = i + dr;
                    int nj = j + dc;

                    // Check if shifted position is inside img2
                    if (ni >= 0 && ni < n &&
                        nj >= 0 && nj < n) {

                        if (img1[i][j] == 1 && img2[ni][nj] == 1) {
                            overlap++;
                        }
                    }
                }
            }

            if (overlap > maxOverlap) {
                maxOverlap = overlap;
            }
        }
    }

    return maxOverlap;
}