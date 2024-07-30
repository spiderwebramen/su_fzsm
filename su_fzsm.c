#include "su_fzsm.h"
#include <ctype.h>
#include <stdbool.h>

bool fuzzy_match_simple(char *pattern, char *string) {
    while (*pattern != '\0' && *string != '\0') {
        if (tolower(*pattern) == tolower(*string)) pattern++;

        string++;
    }

    return *pattern == '\0';
}

int fuzzy_match(char *pattern, char *string) {
    int score = 0;

    bool consecutive_match = false;
    bool consecutive_leading_unmatch = true;
    int consecutive_leading_unmatch_score = 0;
    char prev_char = '\0';

    while (*pattern != '\0' && *string != '\0') {
        if (tolower(*pattern) == tolower(*string)) {
            score += MATCHED_LETTER_BONUS;
            pattern++;

            if (prev_char != '\0') {
                if (prev_char == '_' || prev_char == ' ') {
                    score += SEPARATOR_BONUS;
                } else if (prev_char == tolower(prev_char) &&
                           *string == toupper(*string)) {
                    score += CAMEL_CASE_BONUS;
                }
            } else {
                score += FIRST_LETTER_BONUS;
            }

            if (consecutive_match) { score += CONSECUTIVE_MATCH_BONUS; }
            consecutive_match = true;

            if (consecutive_leading_unmatch) {
                score += consecutive_leading_unmatch_score;
                consecutive_leading_unmatch = false;
            }
        } else {
            consecutive_match = false;
            if ((prev_char == '\0' || consecutive_leading_unmatch) &&
                consecutive_leading_unmatch_score >
                    MAX_UNMATCHED_CONSECUTIVE_LEADING_LETTER_PENALTY) {
                consecutive_leading_unmatch_score +=
                    UNMATCHED_CONSECUTIVE_LEADING_LETTER_PENALTY;
                consecutive_leading_unmatch = true;
            } else {
                score += UNMATCHED_LETTER_PENALTY;
            }
        }

        prev_char = *string;
        string++;
    }

    return score;
}
