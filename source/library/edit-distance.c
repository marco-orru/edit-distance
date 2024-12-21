#include "edit-distance.h"
#include "diagnostics.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/**
 * Returns the minimum between three integers.
 */
inline static int min3i(int a, int b, int c)
{
    int min = a;
    if (b < min)
        min = b;

    if (c < min)
        min = c;

    return min;
}

/**
 * Calculates the minimum edit distance between the two strings.
 */
static int edit_distance_rec(const char *s1, const char *s2)
{
    int d_noop, d_canc, d_ins;

    if (!*s1)
        return (int)strlen(s2);

    if (!*s2)
        return (int)strlen(s1);

    d_noop = (*s1 == *s2) ? edit_distance_rec(s1 + 1, s2 + 1) : INT_MAX;
    d_canc = 1 + edit_distance_rec(s1, s2 + 1);
    d_ins = 1 + edit_distance_rec(s1 + 1, s2);

    return min3i(d_noop, d_canc, d_ins);
}

int edit_distance(const char *s1, const char *s2)
{
    ASSERT_NULL_PARAMETER(s1, edit_distance);
    ASSERT_NULL_PARAMETER(s2, edit_distance);

    return edit_distance_rec(s1, s2);
}

/**
 * Calculates the edit distance between the two strings using memoization.
 */
int edit_distance_dyn_memo(const char *s1, const char *s2, size_t len_s1, size_t len_s2, int **memo)
{
    int d_noop, d_canc, d_ins;

    if (!*s1)
        return (int)len_s2;

    if (!*s2)
        return (int)len_s1;

    if (memo[len_s1 - 1][len_s2 - 1] != -1)
        return memo[len_s1 - 1][len_s2 - 1];

    d_noop = (*s1 == *s2) ? edit_distance_dyn_memo(s1 + 1, s2 + 1, len_s1 - 1, len_s2 - 1, memo) : INT_MAX;
    d_canc = 1 + edit_distance_dyn_memo(s1, s2 + 1, len_s1, len_s2 - 1, memo);
    d_ins = 1 + edit_distance_dyn_memo(s1 + 1, s2, len_s1 - 1, len_s2, memo);

    memo[len_s1 - 1][len_s2 - 1] = min3i(d_noop, d_canc, d_ins);
    return memo[len_s1 - 1][len_s2 - 1];
}

int edit_distance_dyn(const char *s1, const char *s2)
{
    size_t len_s1, len_s2;
    size_t result;
    int **memo;

    ASSERT_NULL_PARAMETER(s1, edit_distance_dyn);
    ASSERT_NULL_PARAMETER(s2, edit_distance_dyn);

    len_s1 = strlen(s1);
    len_s2 = strlen(s2);

    memo = malloc(sizeof(int **) * len_s1);
    for (size_t i = 0; i < len_s1; i++)
    {
        memo[i] = malloc(sizeof(int) * len_s2);
        for (size_t j = 0; j < len_s2; j++)
            memo[i][j] = -1;
    }

    result = edit_distance_dyn_memo(s1, s2, len_s1, len_s2, memo);

    for (size_t i = 0; i < len_s1; i++)
        free(memo[i]);
    free(memo);

    return (int)result;
}