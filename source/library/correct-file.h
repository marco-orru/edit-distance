#pragma once
#include <stdio.h>

/**
 * @brief Reads the words inside the dictionary file and corrects the correct me file according to them.
 *
 * @remarks Dictionary file shall be formatted as a list of words, one per line.
 *
 * @param dictionary Pointer to the dictionary file.
 * @param to_correct Pointer to the file to correct.
 *
 * @note Both dictionary file and correct me file shall be open and dictionary must differ from correct me.
 */
void correct_file(FILE *dictionary, FILE *to_correct);
