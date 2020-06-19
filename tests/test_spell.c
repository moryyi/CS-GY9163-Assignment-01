#include <check.h>
#include <stdlib.h>

#include "../spell-check/dictionary.h"

#define TEST_DICTIONARY_FILENAME "./test_dictionary.txt"
#define COMPLETE_DICTIONARY_FILENAME "./wordlist.txt"
#define TEST_TEXT_FILENAME "./test_text01.txt"

#ifndef MAX_MISSPELLED
#define MAX_MISSPELLED 1000
#endif

/** 
 * Test Case 01 for load_dictionary().
 * Check whether load_dictionary() successfully loads given dictionary.
 */
START_TEST(test_load_normal_dictionary) {
  hashmap_t hashtable[HASH_SIZE];
  bool if_loaded;
  hashmap_t tmp, head;

  if_loaded = load_dictionary(TEST_DICTIONARY_FILENAME, hashtable);
  
  // Check return value of load_dictionary()
  ck_assert_int_eq(true, if_loaded);

  // Check values in hashtable
  /**
   * hash_function("first")   = 552
   * hash_function("second")  = 636
   * hash_function("third")   = 539
   * hash_function("fourth")  = 664
   */
  ck_assert_str_eq("first",   hashtable[552]->word);
  ck_assert_str_eq("second",  hashtable[636]->word);
  ck_assert_str_eq("third",   hashtable[539]->word);
  ck_assert_str_eq("fourth",  hashtable[664]->word);
  
  // Free allocated memory to avoid memory leak.
  for (int i = 0; i < HASH_SIZE; i++) {
    head = hashtable[i];
    while (head != NULL) {
      tmp = head;
      head = head->next;
      free(tmp);
    }
    hashtable[i] = NULL;
  }
} END_TEST

/**
 * Test Case 02 for check_word().
 * Test given words are correctly checked by check_word()
 * 
 */
START_TEST (test_check_word_normal) {
  hashmap_t hashtable[HASH_SIZE];
  hashmap_t head, tmp;
  load_dictionary(COMPLETE_DICTIONARY_FILENAME, hashtable);
    // Words to be checked
  // 1. word containing only letters
  const char* correct_word_01 = "earthling";
  // 2. word containing letters and (')
  const char* correct_word_02 = "earthling's";
  // 3. word containing only digits
  const char* correct_word_03 = "12345";
  // 4. word containing mixed letters and digits
  const char* wrong_word_01 = "earthling123";
  // 5. word not in the dictionary
  const char* wrong_word_02 = "definitenotindictionaryword";

  // check_word() should return true
  ck_assert(check_word(correct_word_01, hashtable));
  ck_assert(check_word(correct_word_02, hashtable));
  ck_assert(check_word(correct_word_03, hashtable));

  // check_word() should return false
  ck_assert(!check_word(wrong_word_01, hashtable));
  ck_assert(!check_word(wrong_word_02, hashtable));

  // Free allocated memory to avoid memory leak.
  for (int i = 0; i < HASH_SIZE; i++) {
    head = hashtable[i];
    while (head != NULL) {
      tmp = head;
      head = head->next;
      free(tmp);
    }
    hashtable[i] = NULL;
  }
} END_TEST

/**
 * Test Case 03 for check_words()
 * Test given text file is correctly checked by check_words()
 */
/**
 * test_text01.txt contains:
 *  1. valid lowercase word
 *  2. valid lowercase word with first character in uppercase
 * 
 *  3. invalid multiple spaces between 2 words
 *  4. invalid multiple punctuations between 2 words
 *  5. invalid english word containing digits
 */
START_TEST(test_check_words_normal) {
  hashmap_t hashtable[HASH_SIZE];
  FILE* fp;
  int num_misspelled;
  char* misspelled[MAX_MISSPELLED];
  char* expected[4];

  expected[0] = "sogn";
  expected[1] = "skyn";
  expected[2] = "b3gin";
  expected[3] = "betta";

  load_dictionary(COMPLETE_DICTIONARY_FILENAME, hashtable);

  // Read given text file.
  fp = fopen(TEST_TEXT_FILENAME, "r");
  if (fp == NULL) {
    ck_assert((fp != NULL));
  }

  // Get all misspelled words in given text file.
  num_misspelled = check_words(fp, hashtable, misspelled);

  // Checke return values.
  ck_assert_int_eq(num_misspelled, 4);
  for (int i = 0; i < num_misspelled; i++) {
    ck_assert_str_eq(misspelled[i], expected[i]);
  }

  // Free allocated memory to avoid memory leak.
  free_memory(hashtable, num_misspelled, misspelled);
} END_TEST


/**
 * Test Suite
 */
Suite* test_spell_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("test_spell");
  tc_core = tcase_create("core");

  // Add test case here
  tcase_add_test(tc_core, test_load_normal_dictionary);
  tcase_add_test(tc_core, test_check_word_normal);
  tcase_add_test(tc_core, test_check_words_normal);

  suite_add_tcase(s, tc_core);

  return s;
}


/**
 * Main test function
 */
int main(void) {
  int failed;
  Suite* suite;
  SRunner* runner;

  suite = test_spell_suite();
  runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
