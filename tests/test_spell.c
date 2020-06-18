#include <check.h>
#include <stdlib.h>

#include "../spell-check/dictionary.h"


/** 
 * Test Case 01.
 * Check whether load_dictionary() successfully loads given dictionary.
 */
START_TEST(test_load_normal_dictionary) {
  hashmap_t hashtable[HASH_SIZE];
  char* test_dictionary_filename = "./test_dictionary.txt";
  bool if_loaded;
  hashmap_t tmp, head;

  if_loaded = load_dictionary(test_dictionary_filename, hashtable);
  
  // 1. Check return value of load_dictionary()
  ck_assert_int_eq(true, if_loaded);

  // 2. Check values in hashtable
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
  
  // 3. Free allocated memory to avoid memory leak.
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
 * Test Suite
 */
Suite* test_spell_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("test_spell");
  tc_core = rcase_create("core");
  
  tcase_add_test(tc_core, test_load_normal_dictionary);

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
