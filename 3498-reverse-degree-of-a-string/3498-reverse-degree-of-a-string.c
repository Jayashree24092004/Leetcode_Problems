int reverseDegree(char* s) {
    int sum = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        int reverseValue = 'z' - s[i] + 1;
        int position = i + 1;

        sum += reverseValue * position;
    }

    return sum;
}