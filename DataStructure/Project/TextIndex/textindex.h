#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SUCCESS 0
#define FAILURE -1
#define NAMELENGTH 20
#define BUFF_SIZE 255
#define INITIAL_SIZE 26

struct word_count_table_t
{
	char word[10];
	int frequency;
};

typedef struct word_count_node
{
	int key;
	struct word_count_table_t *wordFreq;
	struct word_count_node *link;
}Link;


typedef struct file_word_table_t
{
	Link *wordCountTable[INITIAL_SIZE]; //array of pointers to datatype Link
}File_Word_Table;


/* process each file for word_count*/
int process_file(char *pathname);

/* process words and its freq for a given file and insert into HashTable */
int process_word_count(FILE *fd, File_Word_Table *temptable);

/* create a new empty HashTable for a file with word&count*/
void wordCountHTInit(File_Word_Table *temptable);

//create hashtable of word_count struct by reading the file content
int create_HT_of_word_freq(FILE *fd, File_Word_Table *temptable);

// hash function is not case sensitive 
int hash_function(char *value);

//create array of word_count struct by reading the file content
int create_array_of_word_freq(FILE *fd, struct word_count_table_t word_freq[] );
//int create_array_of_word_freq(FILE *fd);

//update the word_count array 	
int update_wordfreq(struct word_count_table_t s[], const char unit[], int count);

// insert the values into hashTable
int hashTableInsert(File_Word_Table *temptable, int key, struct word_count_table_t *tempwordFreq);

//print hashTable
int print_hashTable(File_Word_Table *temptable);

