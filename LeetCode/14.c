#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* LongestPrefix(char* str1, char* str2) {
    int str1Len = strlen(str1);
    int str2Len = strlen(str2);

    char *result = calloc(str1Len + 1, sizeof(char));
    for (int i = 0; i < str1Len && i < str2Len; i++) {
        if (str1[i] == str2[i])
            result[i] = str1[i];
        else
            break;
    }

    return result;
}

char* longestCommonPrefix(char** strs, int strsSize) {
    char *result = calloc(1, sizeof(char));
    if (strsSize < 1)
        return result;

    if (strsSize < 2)
        return strs[0];

    result = LongestPrefix(strs[0], strs[1]);
    if (strsSize < 3)
        return result;

    for (int i = 2; i < strsSize; i++) {
        result = LongestPrefix(result, strs[i]);
    }

    return result;
}

int main() {
    
}