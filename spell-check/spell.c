#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

#define MAX_LINE_LENGTH 2000


// Load words in the dictionary file into the hashtable.
// Assume the hashtable has been initialized properly.
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
  FILE* fp;
  hashmap_t tmp;
  int bucket;
  char line[LENGTH + 1];

  initialize_hashtable(hashtable);
  
  fp = fopen(dictionary_file, "r");
  if (fp == NULL) {
    return false;
  }

  // For wordlist.txt, each line only contains
  // one word less than 45 characters.
  while(fgets(line, LENGTH, fp) != NULL) {
    // Switch the last '\n' character to '\0' if there is
    // a newline in the end of the file.
    if (line[strlen(line) - 1] == '\n')  {
      line[strlen(line) - 1] = '\0';
    }
    bucket = hash_function(line);
    tmp = (hashmap_t)malloc(sizeof(node));
    // memcpy(tmp->word, line, strlen(line));
    strncpy(tmp->word, line, strlen(line));
    tmp->word[LENGTH] = '\0';
    tmp->next = NULL;
    if (hashtable[bucket] == NULL) {
      hashtable[bucket] = tmp;
    }
    else {
      tmp->next = hashtable[bucket];
      hashtable[bucket] = tmp;
    }
  }
  fclose(fp);
  return true;
}

void initialize_hashtable(hashmap_t hashtable[]) {
  // hashmap_t tail;
  for (int i = 0; i < HASH_SIZE; i++) {
    // tail = (hashmap_t)malloc(sizeof(node));
    // memcpy(tail->word, "\x00", LENGTH + 1);
    // tail->next = NULL;
    // hashtable[i] = tail;
    hashtable[i] = NULL;
  }
}

// Check wheter the given word is in the hashtable.
bool check_word(const char* word, hashmap_t hashtable[]) {
  int bucket = hash_function(word);
  char* lower_word = NULL;
  hashmap_t ptr = NULL;

  // 1. Check the original word
  bucket = hash_function(word);
  ptr = hashtable[bucket];
  while (ptr != NULL) {
    if (strncmp(ptr->word, word, strlen(word)) == 0) {
      return true;
    }
    else {
      ptr = ptr->next;
    }
  }

  // 2. Check the lowercase'd word
  lower_word = (char*)malloc(sizeof(char) * (strlen(word) + 1));
  strncpy(lower_word, word, strlen(word) + 1);
  for (int i = 0; i < strlen(lower_word); i++) {
    lower_word[i] = tolower(lower_word[i]);
  }
  bucket = hash_function(lower_word);
  ptr = hashtable[bucket];
  while (ptr != NULL) {
    if (strncmp(ptr->word, lower_word, strlen(lower_word)) == 0) {
      // manually free the allocated lower_word
      free(lower_word);
      lower_word = NULL;
      return true;
    }
    else {
      ptr = ptr->next;
    }
  }

  free(lower_word);
  lower_word = NULL;
  
  // 3. Check whether contains only digits
  if (if_only_digits(word)) {
    return true;
  }

  return false;
}

// Check spelling for all words in the given file.
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {
  int num_misspelled = 0;
  char line[MAX_LINE_LENGTH + 1];
  char word[LENGTH + 1];
  int cur = 0;
  int pre = 0;

  while(fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
    line[MAX_LINE_LENGTH] = '\0';
    // cur == strlen(line): read until the last '\0' character.
    // This enables checker to read the last word if
    // there is no newline in the last of the file.
    while (cur <= strlen(line)) {
      // Separate lines by space or punctuation, etc.
      // cur will keep moving backward if current character
      // is a letter (both upper- and lower-case), digit, or '\''.
      if ((line[cur] >= 'A' && line[cur] <= 'Z')
        || (line[cur] >= 'a' && line[cur] <= 'z')
        || (line[cur] >= '0' && line[cur] <= '9')
        || line[cur] == '\'') {
        // move to next character
        cur += 1;
      }
      else {
        // Avoid empty string slide
        if (cur == pre) {
          // Don't compare with hashmap.
          // Continue to find next word.
        }
        else {
          // (cur - pre) includes the NULL byte at the end.
          strncpy(word, line + pre, cur - pre);
          word[cur - pre] = '\0';

          // Check whether word is spelled correctly (in dictionary)
          // or whether word contains only digits
          if (check_word(word, hashtable)) {
            // word is correctly spelled
          }
          else {
            misspelled[num_misspelled] = (char*)malloc(sizeof(char) * (strlen(word) + 1));
            strncpy(misspelled[num_misspelled], word, strlen(word) + 1);
            num_misspelled += 1;
          }
          memset(word, 0, strlen(word) + 1);
        }

        cur += 1;
        pre = cur;
      }
    }
    // reset pointers
    cur = 0;
    pre = 0;
  }

  return num_misspelled;
}


void free_memory(hashmap_t hashtable[], int num_misspelled, char* misspelled[]) {
  hashmap_t tmp, head;
  for (int i = 0; i < HASH_SIZE; i++) {
    if (hashtable[i] != NULL) {
      head = hashtable[i];
      while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
      }
      hashtable[i] = NULL;
    }
  }

  for (int i = 0; i < num_misspelled; i++) {
    free(misspelled[i]);
    misspelled[i] = NULL;
  }
}


bool if_only_digits(const char* word) {
  // Count the number of digital characters.
  // Return true if strlen(word) == number of digits.
  int length, num_digital;
  
  length = strlen(word);
  num_digital = 0;

  for (int i = 0; i < length; i++) {
    if (word[i] >= 0x30 && word[i] <= 0x39) {
      num_digital += 1;
    }
  }

  if (length == num_digital) {
    return true;
  }
  else {
    return false;
  }
}