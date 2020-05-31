#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

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
  
  fp = fopen(dictionary_file, "r");
  if (fp == NULL) {
    return false;
  }

  initialize_hashtable(hashtable);

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
    memcpy(tail->word, "NULL\x00", 5);
    tail->next = NULL;
    hashtable[i] = tail;
  }
}

// Check wheter the given word is in the hashtable.
bool check_word(const char* word, hashmap_t hashtable[]) {
  int hash = hash_function(word);
  hashmap_t ptr = NULL;

  ptr = hashtable[hash];

  // display all elements in hashtable[hash]
  while (ptr != NULL) {
    printf("%s, ", ptr->word);
    ptr = ptr->next;
  }
  printf("\n");

  printf("strlen(word) = %ld\n", strlen(word));

  ptr = hashtable[hash];
  while (ptr != NULL) {
    if (memcmp(ptr->word, word, strlen(word)) == 0) {
      return true;
    }
    else {
      ptr = ptr->next;
    }
  }
  return false;
}

// Check spelling for all words in the given file.
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {

}
