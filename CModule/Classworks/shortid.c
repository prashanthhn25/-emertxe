#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define MAXPARTICIPANTS 30
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int no_of_participants, iter;
    int participantList[MAXPARTICIPANTS];
    int i, j;
    static int modVal;
    int modShortVals[MAXPARTICIPANTS];
    bool flag = false;
    
    scanf("%d", &no_of_participants);
    
    if (no_of_participants < 1 && no_of_participants > 30) {
        printf("ERROR");
        return 1;
    }
    else
    {
        for(iter = 0; iter < no_of_participants; iter++)
        {
            scanf("%d", &participantList[iter]);
        }
        
        modVal = 0;
        
        do
        {
            
            for(iter = 0; iter < no_of_participants; iter++)
            {
                modShortVals[iter] = participantList[iter] % (2 + modVal);
                printf("%d ",  modShortVals[iter]);
            }
            printf("\n");
        
                //check for unique values
                for(i = 0; i < no_of_participants; i++)
                {
                    for(j= (i+1); j < no_of_participants; j++)
                    {
                        if(modShortVals[j] == modShortVals[i])
                        {
                            flag = true;
                            break;
                        }
                    }
                    if (flag == true)
                    {
                    
                        break;
                    }
                }
                
            if (flag == true)
            {
                break;
            }
            else
            {
                flag = false;
                continue;
            }

            modVal++;
            
        }while(modVal <=5);
        //output: short vals
        printf("%d", (modVal+2));
    }
       return 0;
}
