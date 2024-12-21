#include "diagnostics.h"
#include "correct-file.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Defines constants for indexing `argv`.
 */
enum Args
{
    ARG_DICTIONARY_PATH = 1,
    ARG_INPUT_FILE_PATH
};

/**
 * Processes the input file.
 */
static void process_file(const char *dictionary_path, const char *in_path)
{
    FILE *dictionary_file, *in_file_file;

    dictionary_file = fopen(dictionary_path, "r");
    in_file_file = fopen(in_path, "r");

    ASSERT(dictionary_file, "Unable to open the dictionary file", process_file);
    ASSERT(in_file_file, "Unable to open the file to be corrected", process_file);

    correct_file(dictionary_file, in_file_file);

    ASSERT(!fclose(in_file_file), "Unable to close the file to be corrected", process_file);
    ASSERT(!fclose(dictionary_file), "Unable to close the dictionary file", process_file);
}

/**
 * Entry point.
 */
int main(int argc, char *argv[])
{
    const char *dictionary_path;
    const char *in_file_path;

    ASSERT(argc > ARG_DICTIONARY_PATH, "Wrong number of arguments (dictionary file path not found)", main);
    ASSERT(argc > ARG_INPUT_FILE_PATH, "Wrong number of arguments (input file path not found)", main);

    dictionary_path = argv[ARG_DICTIONARY_PATH];
    in_file_path = argv[ARG_INPUT_FILE_PATH];

    process_file(dictionary_path, in_file_path);

    return EXIT_SUCCESS;
}