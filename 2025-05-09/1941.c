bool areOccurrencesEqual(char* s) {
    int accepted_frequency = 0;
    char verified_chars[27] = "";
    
    for (int i = 0; i < strlen(s); i++) {
        if (strchr(verified_chars, s[i]) != NULL)
            continue;
        
        int frequency = 0;

        char single_char[] = "";
        single_char[0] = s[i];
        strncat(verified_chars, single_char, 1);

        for (int j = i; j < strlen(s); j++) {
            if (s[j] == s[i])
                frequency++;
        }

        if (accepted_frequency == 0)
            accepted_frequency = frequency;
        else {
            if (frequency != accepted_frequency) {
                return false;
            }
        }
    }

    return true;
}