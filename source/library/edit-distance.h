#pragma once

/**
 * @brief Calculates the edit distance between the two strings.
 *
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @returns The edit distance between the two strings.
 */
int edit_distance(const char *s1, const char *s2);

/**
 * @brief Calculates the edit distance between the two strings using dynamic programming.
 *
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @returns The edit distance between the two strings.
 */
int edit_distance_dyn(const char *s1, const char *s2);
