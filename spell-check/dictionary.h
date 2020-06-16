#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdio.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

#define HASH_SIZE 2000

#define MAX_MISSPELLED 1000

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

typedef node* hashmap_t;

// Hash table is an array of linked lists.
node* hashtable[HASH_SIZE];

/**
 * Array misspelled is populated with words that are misspelled. Returns the length of misspelled.
 */
/**
 * Inputs:
 *  fp:         A file pointer to the document to check for spelling errors.
 *  hashtable:  The hash table used to determine spelling
 *  misspelled: An empty char* array to be populated with misspelled words.
 *              This array will never be greater than 1000 words long.
 *            
 * Returns:
 *  int:        The number of words in the misspelled arary.
 *
 * Modifies:
 *  misspelled: This array will be filled with misspelled words.
 *
 * Example:
 *  int num_misspelled = check_words(text_file, hashtable, misspelled);
 **/
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]);

/**
 * Returns true if word is in dictionary else false.
 */
/**
 * Inputs:
 *  word:       A word to check the spelling of.
 *  hashtable:  The hash table used to determine spelling
 *            
 * Returns:
 *  bool:       A boolean value indicating if the word was correctly spelled.
 *
 * Modifies:
 *  
 * Example:
 *  bool correct  = check_word(word, hashtable);
 **/
bool check_word(const char* word, hashmap_t hashtable[]);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
/**
 * Inputs:
 *  dictionary_file:    Path to the words file.
 *  hashtable:          The hash table to be populated.
 *            
 * Returns:
 *  bool:       Whether or not the hashmap successfully populated.
 *
 * Modifies:
 *  hashtable: This hashmap should be filled with words from the file provided.
 *
 * Example:
 *  bool success = load_dictionary("wordlist.txt", hashtable);
 **/
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]);

/**
 * Initialize the hashtable with NULL.
 **/
/**
 * Inputs:
 *  hashtable:          The hash table to be populated.
 *            
 * Modifies:
 *  hashtable: This hashmap should be filled with NULL on each element.
 *
 * Example:
 *  initialize_hashtable(hashtable);
 **/
void initialize_hashtable(hashmap_t hashtable[]);

/**
 * Returns true if word contains only digits else false.
 */
/**
 * Inputs:
 *  word:       A word to check the spelling of.
 *            
 * Returns:
 *  bool:       A boolean value indicating if the word contains only digits.
 *
 * Modifies:
 *  
 * Example:
 *  bool correct  = if_only_digits(word);
 **/
bool if_only_digits(const char* word);

/**
 * Free allocated heap memory for hashtable and misspelled words.
 **/
/**
 * Inputs:
 *  hashtable:          The hash table to be freed.
 *  misspelled:         The misspelled 2d array to be freed.
 * 
 * Modifies:
 * 
 * Example:
 *  free_memory(hashtable, misspelled);
 **/
void free_memory(hashmap_t hashtable[], int num_misspelled, char * misspelled[]);

/**
 * Already implemented in dictionary.c
 **/
int hash_function(const char* word);

#endif // DICTIONARY_H