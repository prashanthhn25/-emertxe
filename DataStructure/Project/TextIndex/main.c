#include "textindex.h"

int main(int argc, char **argv)
{
	int i, fileCount = 0, fileTotalCount = 0;
	int choice;
	char option;
	char searchWord[NAMELENGTH];
     
	//File_Word_Table  file_database_array[10];
	File_Word_Table  *file_database_array;
	file_database_array = (File_Word_Table *)malloc(10 * sizeof(File_Word_Table));
		
	//check for argc
	if(argc < 2)
	{
		printf("Invalid arguments.\n");
		printf("Usage: ./a.out <file> [FILES..] \n");
		return -1;
	}

	do
	{
		printf("Enter the option:\n");
		printf("1. Search for a word\n");	
		printf("2. Save the database\n");	
		printf("3. Update to existing database\n");	
		printf("4. Destroy HashTable\n");
		printf("5. Print Database\n");
		printf("6. initialization\n");
		
		printf("Choice: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				
				printf("Enter the word to be searched: \n");
				scanf("%s", searchWord);
				
				for(i = 0; i < fileTotalCount; i++)
				{
					//print_hashTable(file_database_array[i]);
					//to search that element
					if(hashTableSearch(&file_database_array[i], searchWord) == SUCCESS)
					{
						printf("SUCCESS: element found\n");
					}
					else
					{
						printf("FAILURE: no element found\n");
					}
					printf("\n");
				}

				break;
			case 2:
				for(i = 0; i < fileTotalCount; i++)
				{
					save_to_database(&file_database_array[i]);
				}
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				for(i = 0; i < fileTotalCount; i++)
				{
					print_hashTable(&file_database_array[i]);
				}
				break;
			case 6: 
				
				fileTotalCount = argc -1;
				//when files are given
				for (i = 1; i < argc; i++)
				{
					File_Word_Table file_words;	//file and words hashtable

					//initialize the table for words in a file
					wordCountHTInit(&file_words);
       
					//process the files to get wordcount and save it in the database
					if (process_file(argv[i], &file_words ) == FAILURE)
					{
						printf("processing the file failed.\n");
						return -1;
					}
		
					//update the database array for all files
					//fileCount = update_database(&file_database_array, file_words, fileCount);

					printf("adrees is: %p\n", &file_words);
					file_database_array[i-1] = file_words;
					printf("adrees is: %p\n", &file_database_array);
					
					//print hashtable
					print_hashTable(&file_database_array[i-1]);

				}

			break;
			default:
				printf("Invalid option\n");
				break;

		}

		/* check for continue */
        	printf("Continue (y/n): ");
        	scanf("\n%c", &option);
            
    	} while (option == 'y');
	return 0;

}

int update_database(File_Word_Table *s[], const File_Word_Table unit, int count)
{
   *s[count] = unit;
    
    // count represents the number of fields updated in array s
    return (count + 1);
}

void wordCountHTInit(File_Word_Table *temptable)
{
	
    	int i;

	//initialize the values for the table
		
	for( i = 0; i < INITIAL_SIZE; i++)
	{
		//temptable -> wordCountTable[i] = (Link *)malloc(INITIAL_SIZE * sizeof(Link));
		temptable -> wordCountTable[i] = NULL;
	}
	

}

// to process words i.e to open the file, get the words and its each count and update the hashtable
int process_file(char *pathname, File_Word_Table *temptable)
{
	FILE *fd;
	
	/* To open file to read */
	fd = fopen(pathname, "r");
        if (NULL == fd)
        {
            perror("fopen");
            return FAILURE;
        }

	//initialize the value of the filename
	strcpy(temptable -> fileName, pathname);

	/* to get the words and its count in the file */
	if ( process_word_count(fd, temptable) == FAILURE )
	{
		perror("process_word_count");
		return FAILURE;	
	}

	/* close the file */
	fclose(fd);

	return SUCCESS;	
}

int process_word_count(FILE *fd, File_Word_Table *temptable)
{
	int i;
	int key;

	struct word_count_table_t word_freq_array[BUFF_SIZE + 1]; //array of datatype struct word_count_table_t
	int total_word_count = 0;

	//create array of word_count struct
	total_word_count = create_array_of_word_freq(fd, word_freq_array);

	//to generate key for each words from word_freq_array and insert into hashtable
	for (i = 0; i < total_word_count; i++)
	{
		//to generate key 
        	key = hash_function(word_freq_array[i].word);
		printf(" %s\t   %d : %d\n", word_freq_array[i].word, word_freq_array[i].frequency, key);
		//insert the values in the hash table
		hashTableInsert(temptable, key, &word_freq_array[i]);
      	}
	printf("\n");
}		

int create_array_of_word_freq(FILE *fd, struct word_count_table_t word_freq[] )
{
	char unit[BUFF_SIZE + 1];
	int i = 0, freq = 0, j = 0, count = 0;

	int read_len;
	char buff[BUFF_SIZE + 1];

	//initialize frequency to 0
	for (i = 0; i <= BUFF_SIZE; i++)
	{
       		word_freq[i].frequency = 0;
    	}	

	//read the file and store all the words in a buff
	{
		if ((read_len = fread(buff, sizeof(char), BUFF_SIZE, fd)) == 0) 
		{
		        fputs("Error reading file", stderr);
    		} 
		else 
		{
		        buff[read_len++] = '\0'; /* Just to be safe. */
		}    

		//buff has the entire data and is now a string
		
		//get each words and save in unit and update the struct
		for (i = 0; i < strlen(buff); i++)
    		{
			//get only the word
        		while (i < strlen(buff) && buff[i] != ' ' && isalnum(buff[i]))
        		{
            			unit[j++] = buff[i++]; 
        		}
			//update the struct with the word and word frequency
        		if (j != 0)
        		{
            			unit[j] = '\0';
				//count and save the number of occurances of each word
            			count = update_wordfreq(word_freq, unit, count);
            			j = 0;
        		}
    		}	
	          
       		return count;
    	}

}

int update_wordfreq(struct word_count_table_t s[], const char unit[], int count)
{
    int i;
 
    for (i = 0; i < count; i++)
    {
        if (strcmp(s[i].word, unit) == 0)
        {
            s[i].frequency++;
            return count;
        }
    }

    // If control reaches here, it means no match found in struct
    strcpy(s[count].word, unit);
    s[count].frequency++;
 
    // count represents the number of fields updated in array s
    return (count + 1);
}


int hash_function(char *value)
{
	int key;
	int i;	
	

	//takes mod of 26 for the first character of the value
	//a/A = 0.... z/Z =25
	
	//to ignore case-senstitivity
	if (*value >= 'A' && *value <= 'Z') 
	{
		key = *value - 'A';
	}
	else if (*value >= 'a' && *value <= 'z') 
	{
		key = *value - 'a';
	}

	//key value to map to the hashtable
	key = key % INITIAL_SIZE;	
    	return key;
}


int hashTableInsert(File_Word_Table *temptable, int key, struct word_count_table_t *tempwordFreq)
{
	
	//create newNode and update newnode data and link
	Link *new = malloc(sizeof(Link));

	//memory for the node
	if (NULL == new)
	{
		return FAILURE;
	}

	//create a node using the key and value
	new -> key = key;
	new -> wordFreq = tempwordFreq;
	new -> link = NULL;
	
	//take local reference
	Link *temp = temptable -> wordCountTable[key];
	
	//update the links and the pointer to the link in the table
	//when no elements are added yet	
	if(temptable -> wordCountTable[key] == NULL)
	{
		temptable -> wordCountTable[key] = new;
		return SUCCESS;
	}
	else
	{
		//go till the last node
		while(temp -> link)
		{
			temp = temp -> link;
		}
		//update the last node with new 
		temp -> link = new;
 		return SUCCESS;	
	}
	return FAILURE;
}

int print_hashTable(File_Word_Table *temptable)
{
	int i;	
	
	//take local reference to Link
	Link *element;
	
	printf("%s has:\n", temptable -> fileName);
	//iterate through each link in each table row
	for(i = 0; i < INITIAL_SIZE; i++)
	{
		for(element = temptable -> wordCountTable[i]; element != NULL; element = element -> link)
		{
			//print values
			printf("%s ", element -> wordFreq -> word);
					
		}
		printf("; ");	
	}
	printf("\n");	
}

int hashTableSearch(File_Word_Table *temptable, char *value)
{


	//print hashtable
	print_hashTable(temptable);
	
	int key;
	
	//get the key value for the given value
	key = hash_function(value);	
	
	printf("key :---> %d\n", key);
	
	//take local reference to traverse through the list
	Link *temp;
	temp = temptable -> wordCountTable[key];
	
	//if no elements at all then do nothing	
	if(temptable -> wordCountTable[key] == NULL)
	{
		return NOELEMENT;
	}
	else
	{
		printf("word : ---> %s\n", temptable -> wordCountTable[key] ->  wordFreq -> word);
	
		/* if list has multiple nodes then, iterate till tail node */
         	while (temp)
         	{
			if(strcmp((temp -> wordFreq -> word), value) == 0)
			{
				printf("%s :\t", temptable -> fileName);
				//print values
				printf("%s \t", temp -> wordFreq -> word);
				printf("%d \n", temp -> wordFreq -> frequency);
				return SUCCESS;
			}
			temp = temp -> link;
		}
		return FAILURE;
	}
	
}

int save_to_database(File_Word_Table *temptable)
{
	FILE *fd;
	
	/* To open file to read */
	fd = fopen("backup_database.txt", "a");
        if (NULL == fd)
        {
            perror("fopen");
            return FAILURE;
        }

	save_hashTable(fd, temptable);
	
	/* close the file */
	fclose(fd);

	return SUCCESS;	
}

void save_hashTable(FILE *fd, File_Word_Table *temptable)
{
	int i;	
	
	//take local reference to Link
	Link *element;
	
	fprintf(fd, "%s:", temptable -> fileName);
	//iterate through each link in each table row
	for(i = 0; i < INITIAL_SIZE; i++)
	{
		for(element = temptable -> wordCountTable[i]; element != NULL; element = element -> link)
		{
			//print values
			fprintf(fd, "%s ", element -> wordFreq -> word);
			fprintf(fd, "%d ", element -> wordFreq -> frequency);
		}
		fprintf(fd,"; ");	
	}

	fprintf(fd, "\n");
}
