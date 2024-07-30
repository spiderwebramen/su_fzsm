#ifndef SU_FZSM_H
#define SU_FZSM_H

#include <stdbool.h>

#define MATCHED_LETTER_BONUS 0
#define CONSECUTIVE_MATCH_BONUS 15
#define SEPARATOR_BONUS 10
#define CAMEL_CASE_BONUS 10
#define FIRST_LETTER_BONUS 10

#define UNMATCHED_LETTER_PENALTY -1
#define UNMATCHED_CONSECUTIVE_LEADING_LETTER_PENALTY -2
#define MAX_UNMATCHED_CONSECUTIVE_LEADING_LETTER_PENALTY -6

int fuzzy_match(char *pattern, char *string);
bool fuzzy_match_simple(char *pattern, char *string);

#endif // SU_FZSM_H
