#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

#define MAX_LINE_LENGTH 2000


// // Hash table is an array of linked lists.
// node* hashtable[HASH_SIZE];

// Maps a word to an integer value to place it in the hash table.
// Sum the value of each character in the word, then find the 
// remainder after dividing by the size of the hash table.
int hash_function(const char* word)
{
    int sum = 0;
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++)
    {
        sum += word[i];
    }
    
    int bucket = sum % HASH_SIZE;
    return bucket;
}

// Load words in the dictionary file into the hashtable.
// Assume the hashtable has been initialized properly.
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
  FILE* fp;
  hashmap_t tmp;
  int hash;
  char line[LENGTH + 1];

  initialize_hashtable(hashtable);
  
  fp = fopen(dictionary_file, "r");
  if (fp == NULL) {
    return false;
  }

  // For wordlist.txt, each line only contains
  // one word less than 45 characters.
  while(fgets(line, LENGTH, fp) != NULL) {
    line[strlen(line) - 1] = '\0';
    hash = hash_function(line);
    tmp = (hashmap_t)malloc(sizeof(node));
    memcpy(tmp->word, line, strlen(line));
    tmp->next = hashtable[hash];
    hashtable[hash] = tmp;
  }
  return true;
}

void initialize_hashtable(hashmap_t hashtable[]) {
  hashmap_t tail;
  for (int i = 0; i < HASH_SIZE; i++) {
    tail = (hashmap_t)malloc(sizeof(node));
    memcpy(tail->word, "\x00", 5);
    tail->next = NULL;
    hashtable[i] = tail;
  }
}

// Check wheter the given word is in the hashtable.
bool check_word(const char* word, hashmap_t hashtable[]) {
  int hash = hash_function(word);
  hashmap_t ptr = NULL;

  ptr = hashtable[hash];
  while (ptr != NULL) {
    if (memcmp(ptr->word, word, strlen(word)) == 0) {
      // Ensure the word are not missing ending characters
      if (strlen(word) == strlen(ptr->word)) {
        return true;
      }
      else {
        // Continue to next word
      }
    }
    else {
      // Continue to next word
    }
    ptr = ptr->next;
  }
  return false;
}

// Check spelling for all words in the given file.
// [TODO]:
//    [ ] 1. check words contains only numbers <- should be correct spelled.
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
      if (line[cur] != ' ' && line[cur] != '\n' && line[cur] != '\0') {
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
          memcpy(word, line + pre, cur - pre);
          word[cur - pre] = '\0';
          if (check_word(word, hashtable)) {
            // word is correctly spelled
          }
          else {
            misspelled[num_misspelled] = (char*)malloc(sizeof(char) * (strlen(word) + 1));
            strncpy(misspelled[num_misspelled], word, strlen(word));
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
