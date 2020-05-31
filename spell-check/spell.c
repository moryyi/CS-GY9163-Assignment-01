#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// @macro DEBUG : used for main function
#define DEBUG

// int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]);
// bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]);
// bool check_word(const char* word, hashmap_t hashtable[]);


#ifdef DEBUG
int main(int argc, char* argv[]) {
  char* dictionary_file = "wordlist.txt";
  bool ifLoadedSuccess = load_dictionary(dictionary_file, hashtable);

  if (ifLoadedSuccess) {
    char* testword = "ethologist's";
    bool ifSpelledCorrect = check_word(testword, hashtable);
    printf("If spelled correct: %s\n", ifSpelledCorrect ? "true" : "false");
  }
  else {
    printf("[Error] Failed in loading dictionary file.\n");
  }
  return 0;
}
#else
int main(int argc, char* argv[]) {
  return 0;
}
#endif