#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

char* gcdOfStrings(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *combined1 = malloc(len1 + len2 + 1);
    char *combined2 = malloc(len1 + len2 + 1);

    strcpy(combined1, str1);
    strcat(combined1, str2);

    strcpy(combined2, str2);
    strcat(combined2, str1);

    if (strcmp(combined1, combined2) != 0) {
        free(combined1);
        free(combined2);
        return "";
    }

    int len = gcd(len1, len2);

    char *result = malloc(len + 1);
    strncpy(result, str1, len);
    result[len] = '\0';

    free(combined1);
    free(combined2);

    return result;
}