#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../spell-check/dictionary.h"


int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("[Error] Invalid arguments.\n");
    printf("Usage: test_spell <text_file> <dictionary_file>\n");
    return -1;
  }
  char* text_file = argv[1];
  char* dictionary_file = argv[2];

  bool ifLoadedSuccess = load_dictionary(dictionary_file, hashtable);
  FILE* fp;
  
  if (!ifLoadedSuccess) {
    printf("[Error] Failed in loading dictionary file.\n");
    return -1;
  }

  fp = fopen(text_file, "r");
  if (fp == NULL) {
    return -1;
  }

  char* misspelled[MAX_MISSPELLED];
  int num_misspelled = check_words(fp, hashtable, misspelled);
  
  printf("num_misspelled = %d\n", num_misspelled);
  int ptr = 0;
  for (ptr = 0; ptr < num_misspelled; ptr++) {
    printf("misspelled : %s\n", misspelled[ptr]);
  }
  
  // cleanup
  fclose(fp);
  free_memory(hashtable, num_misspelled, misspelled);

  return 0;
}