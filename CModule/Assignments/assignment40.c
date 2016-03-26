/*  
 *  Q. Implement string functions strstr, strtok, strcmp, strncmp, memmove
 *
 *  strstr
 *  ------
 *  a. Read string1 and string2 from user.
 *  b. Call my_strstr function as my_strstr(string1, string2);
 *  c. If string2 pattern is existing within string1 pattern, 
 *      then return the starting location of the first pattern
 *      in string1.
 *
 *  Note: Implement as standard function strstr
 *
 *  Hint: Read man strstr
 *
 *  Concepts to apply:
 *  ------------------
 *  Pointer Concepts
 *  string concepts
 *
 *  Sample Execution:
 *  -----------------
 *
 *  Enter string1: Hello World by Dennis and Hello World by Bjarne
 *  Enter string2: World
 *
 *  World by Dennis and Hello World by Bjarne
 *
 *  strtok
 *  ------
 *  a. Read string1 and string2 from user.
 *  b. Call my_strtok(string1, string2);
 *  c. Should treat string2 as delimitter in string1 and 
 *      should return 1st field.
 *  d. If you call again my_strtok(NULL, string2), 
 *      it should return second field in string1 treating 
 *      string2 as delimitter.
 *
 *  Hint: Read man strtok
 *  Note: Implement as standard function strtok
 *
 *  Concepts to apply:
 *  ------------------
 *  Pointer Concepts
 *  string concepts
 *  static storage class
 *
 *  Sample Execution:
 *  -----------------
 *
 *  Enter string1: Hello World Dennis World Ritchie World
 *  Enter string2: World
 *
 *  Hello
 *
 *  strcmp
 *  ------
 *
 *  a. Read string1 and string2 from user.
 *  b. Call my_strcmp(string1, string2)
 *  c. Should return integer number which indicates both 
 *      string are equal or not.
 *
 *  Hint: Read man strcmp
 *  Note: Implement as standard function strcmp
 *
 *  Concepts to apply:
 *  ------------------
 *  Pointer Concepts
 *  String concepts
 *
 *  Sample Execution:
 *  -----------------
 *
 *  Enter string1: HelloW World
 *  Enter string2: Hello World
 *
 *  String1 and string2 differ
 *
 *  memmove
 *  -------
 *  a. Read an array of integers from user.
 *  b. Read two locations and number of bytes to copy from user.
 *  c. Copy the content of location1 to location2.
 *
 *  Hint: Read man memmove
 *  Note: Implement as standard function memmove
 *
 *  Concepts to apply:
 *  ------------------
 *  void pointer concepts
 *
 *  Sample Execution:
 *  -----------------
 *
 *  Enter array of 5 integers: 10 20 30 40 50
 *
 *  Enter location1: 3
 *  Enter location2: 0
 *  Number of bytes to copy: 8
 *
 *  Array: 30 40 30 40 50
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
    
    return 0;
}
