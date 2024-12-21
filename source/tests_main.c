#include <stdlib.h>
#include <stdio.h>
#include "diagnostics.h"
#include "unity.h"
#include "edit-distance.h"

void test_identical_strings(void)
{
    TEST_ASSERT_EQUAL_INT(0, edit_distance("identical", "identical"));
}

void test_one_empty_string(void)
{
    TEST_ASSERT_EQUAL_INT(4, edit_distance("", "test"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance("test", ""));
    // distance of longest.
}

void test_different_strings(void)
{
    TEST_ASSERT_EQUAL_INT(6, edit_distance("exams", "exaustive"));
    // remove 'u' - add 'm'
    // add 't' - add 'i'
    // add 'v' - add 'e'
}

void test_strings_with_different_lengths(void)
{
    TEST_ASSERT_EQUAL_INT(4, edit_distance("rail", "railroad"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance("railroad", "rail"));
    // remove 'r' - remove 'o' - remove 'a' - remove 'd'
    // add 'r' - add 'o' - add'a' - add 'd'
}

void test_strings_with_one_character_different(void)
{
    TEST_ASSERT_EQUAL_INT(2, edit_distance("furry", "ferry"));
    // remove 'e' - add 'u'
}

void test_project_strings(void)
{
    TEST_ASSERT_EQUAL_INT(1, edit_distance("casa", "cassa"));
    TEST_ASSERT_EQUAL_INT(2, edit_distance("casa", "cara"));
    TEST_ASSERT_EQUAL_INT(2, edit_distance("vinaio", "vino"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance("tassa", "passato"));
    TEST_ASSERT_EQUAL_INT(0, edit_distance("pioppo", "pioppo"));
}

void test_identical_strings_dyn(void)
{
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn("identical", "identical"));
}

void test_one_empty_string_dyn(void)
{
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("", "test"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("test", ""));
    // distance of longest.
}

void test_different_strings_dyn(void)
{
    TEST_ASSERT_EQUAL_INT(6, edit_distance_dyn("exams", "exaustive"));
    // remove 'u' - add 'm'
    // add 't' - add 'i'
    // add 'v' - add 'e'
}

void test_strings_with_different_lengths_dyn(void)
{
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("rail", "railroad"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("railroad", "rail"));
    // remove 'r' - remove 'o' - remove 'a' - remove 'd'
    // add 'r' - add 'o' - add'a' - add 'd'
}

void test_strings_with_one_character_different_dyn(void)
{
    TEST_ASSERT_EQUAL_INT(2, edit_distance_dyn("furry", "ferry"));
    // remove 'e' - add 'u'
}

void test_project_strings_dyn(void)
{
    TEST_ASSERT_EQUAL_INT(1, edit_distance_dyn("casa", "cassa"));
    TEST_ASSERT_EQUAL_INT(2, edit_distance_dyn("casa", "cara"));
    TEST_ASSERT_EQUAL_INT(2, edit_distance_dyn("vinaio", "vino"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("tassa", "passato"));
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn("pioppo", "pioppo"));
}

void setUp(void) {}

void tearDown(void) {}

int main(void)
{
    UNITY_BEGIN();

    printf("----TEST: edit_distance...----\n");

    RUN_TEST(test_identical_strings);
    RUN_TEST(test_one_empty_string);
    RUN_TEST(test_different_strings);
    RUN_TEST(test_strings_with_different_lengths);
    RUN_TEST(test_strings_with_one_character_different);
    RUN_TEST(test_project_strings);

    printf("\n----TEST: edit_distance_dyn...----\n");

    RUN_TEST(test_identical_strings_dyn);
    RUN_TEST(test_one_empty_string_dyn);
    RUN_TEST(test_different_strings_dyn);
    RUN_TEST(test_strings_with_different_lengths_dyn);
    RUN_TEST(test_strings_with_one_character_different_dyn);
    RUN_TEST(test_project_strings_dyn);

    return UNITY_END();
}