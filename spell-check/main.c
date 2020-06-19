#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// @macro DEBUG : used for main function
#define DEBUG


#ifdef DEBUG
int main(int argc, char* argv[]) {
  // char* dictionary_file = "wordlist.txt";
  char* dictionary_file = "test_dictionary.txt";
  char* filename = "test_words.txt";

  int ptr = 0;
  bool ifLoadedSuccess = load_dictionary(dictionary_file, hashtable);
  FILE* fp;
  
  if (!ifLoadedSuccess) {
    printf("[Error] Failed in loading dictionary file.\n");
    return -1;
  }

  fp = fopen(filename, "r");
  if (fp == NULL) {
    return -1;
  }

  char* misspelled[MAX_MISSPELLED];
  int num_misspelled = check_words(fp, hashtable, misspelled);
  
  printf("num_misspelled = %d\n", num_misspelled);
  for (ptr = 0; ptr < num_misspelled; ptr++) {
    printf("misspelled : %s\n", misspelled[ptr]);
  }

  int value = hash_function("first");
  printf("hash_function(\"first\") = %d\n", value);
  printf("hashtable[%d]->word = %s\n", value, hashtable[value]->word);
  int if_same = strcmp("first", hashtable[value]->word);
  printf("strcmp() = %d\n", if_same);
  // cleanup
  fclose(fp);
  free_memory(hashtable, num_misspelled, misspelled);

  return 0;
}
#else
int main(int argc, char* argv[]) {
  return 0;
}
#endif