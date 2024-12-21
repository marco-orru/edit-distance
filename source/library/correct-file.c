#include "correct-file.h"
#include "diagnostics.h"
#include "edit-distance.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef _MSC_VER
#define INT_MAX __INT_MAX__
#endif

/**
 * Maximum length of a word (used in read_next_word)
 */
#define MAX_WORD_LENGTH 64

/**
 * Initial capacity of min distance word buffer.
 */
#define WORD_BUFFER_INITIAL_CAPACITY 4

/**
 * Calculates the size of the dictionary (in bytes) and how many words are inside it.
 */
static size_t analyze_dictionary_file(FILE *dictionary, size_t *n_lines)
{
    size_t size;
    int chr;

    *n_lines = 1;

    while ((chr = fgetc(dictionary)) != EOF)
    {
        if (chr == '\n')
            (*n_lines)++;
    }

    size = ftell(dictionary);
    rewind(dictionary);

    return size + 1;
}

/**
 * Reads the dictionary into the string pool and populates the dictionary entries array.
 */
static void read_dictionary(FILE *dictionary, char *string_pool, char **dictionary_entries)
{
    char line[512];
    size_t dictionary_entry_id;

    dictionary_entry_id = 0;

    while (fgets(line, 512, dictionary))
    {
        dictionary_entries[dictionary_entry_id++] = string_pool;

        for (char *c = line; *c != '\n'; c++)
        {
            *string_pool = *c;
            string_pool++;
        }

        *string_pool = '\0';
        string_pool++;
    }
}

/**
 * Reads the next alphabetic word from the correct me file.
 */
static char *read_next_word(FILE *correct_me)
{
    static char word_buffer[MAX_WORD_LENGTH];
    size_t i;
    int chr;

    while ((chr = fgetc(correct_me)) != EOF && !isalpha(chr))
        ;

    if (feof(correct_me))
        return NULL;

    i = 0;

    do
    {
        word_buffer[i++] = (char)tolower((char)chr); // Converts string to lowercase.
    } while ((chr = fgetc(correct_me)) != EOF && isalpha(chr));

    word_buffer[i] = '\0';
    return word_buffer;
}

/**
 * Prints the minimum edit distances for all the words in the correct me file according to the words defined into the dictionary.
 */
static void print_min_edit_dist(FILE *correct_me, char **dictionary_entries, size_t dictionary_entries_len)
{
    char *word;
    char **words_buffer;
    size_t words_buffer_capacity, words_buffer_size;
    int current_edit_distance, min_edit_distance;
    size_t i;

    words_buffer = malloc(sizeof(char **) * WORD_BUFFER_INITIAL_CAPACITY);
    words_buffer_capacity = WORD_BUFFER_INITIAL_CAPACITY;

    ASSERT(words_buffer, "Unable to allocate memory for the words buffer", print_min_edit_dist);

    while ((word = read_next_word(correct_me)))
    {
        words_buffer_size = 0;
        min_edit_distance = INT_MAX;

        printf("Processing word '%s' (0/%zu)...", word, dictionary_entries_len);
        fflush(stdout);

        for (i = 0; i < dictionary_entries_len; i++)
        {
            if (i % 10000 == 0)
            {
                printf("\rProcessing word '%s' (%zu/%zu)...", word, i, dictionary_entries_len);
                fflush(stdout);
            }

            if (dictionary_entries[i] == NULL)
                continue;

            current_edit_distance = edit_distance_dyn(word, dictionary_entries[i]);

            if (current_edit_distance > min_edit_distance)
                continue;

            if (current_edit_distance < min_edit_distance)
            {
                words_buffer_size = 0;
                min_edit_distance = current_edit_distance;
            }

            if (current_edit_distance == min_edit_distance)
            {
                words_buffer[words_buffer_size++] = dictionary_entries[i];

                if (words_buffer_size >= words_buffer_capacity)
                {
                    words_buffer_capacity *= 2;

                    words_buffer = realloc(words_buffer, sizeof(char **) * words_buffer_capacity);
                    ASSERT(words_buffer, "Unable to reallocate the words buffer array", print_min_edit_dist);
                }
            }

            if (current_edit_distance == 0)
                break;
        }

        printf("\rProcessing word '%s' (%zu/%zu)...", word, i, dictionary_entries_len);
        printf("\n");

        if (min_edit_distance == 0)
        {
            printf("The word '%s' is correct.", word);
        }
        else
        {
            printf("Minimum edit distance for word '%s' is %d: ", word, min_edit_distance);

            for (i = 0; i < words_buffer_size; i++)
                printf("%s, ", words_buffer[i]);

            printf("\b\b  ");
        }

        printf("\n\n");
    }

    free(words_buffer);
}

void correct_file(FILE *dictionary, FILE *correct_me)
{
    char *string_pool;
    size_t string_pool_len;
    char **dictionary_entries;
    size_t dictionary_entries_len;

    ASSERT_NULL_PARAMETER(dictionary, correct_file);
    ASSERT_NULL_PARAMETER(correct_me, correct_file);

    string_pool_len = analyze_dictionary_file(dictionary, &dictionary_entries_len);

    string_pool = malloc(sizeof(char) * string_pool_len);
    dictionary_entries = malloc(sizeof(char **) * dictionary_entries_len);

    ASSERT(string_pool, "Unable to allocate memory for the dictionary string pool", correct_file);
    ASSERT(dictionary_entries, "Unable to allocate memory for the dictionary entries", correct_file);

    printf("Reading dictionary file...\n");
    read_dictionary(dictionary, string_pool, dictionary_entries);

    printf("Analyzing text...\n\n");
    print_min_edit_dist(correct_me, dictionary_entries, dictionary_entries_len);

    free(dictionary_entries);
    free(string_pool);
}