/*
 * Image Stegnography
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encdecflag = 0;

int main(int argc, char **argv)
{

    char *txtfileName, *bmpfileName, *encryptbmpfileName ;
    
    FILE *secretfile, *bmpfile, *encrptfile;
    
    int txtFileSize, bmpFileSize;
    
    /* Do arg count check */
    if (argc < 2)
    {
        fprintf(stderr, "ERROR: Invalid arguments. Try any of the below said format \n");
        fprintf(stderr, "USAGE: lsb_steg -e secret.txt image.bmp encrypted.bmp \n");
        fprintf(stderr, "USAGE: lsb_steg -e secret.txt image.bmp \n");
        fprintf(stderr, "USAGE: ./lsb_steg -d encrpted.bmp message.txt\n");
        fprintf(stderr, "USAGE: ./lsb_steg -d encrpted.bmp \n");
        exit(1);
    }
    else
    {
        /* check for processing optional arguments for Encryption */
        if (strcmp(argv[1], "-e") == 0)
        {
            encdecflag = 1;  /* This is used as a boolean value. */
        }
        else if (strcmp(argv[1], "-d") == 0)
        {
            encdecflag = 2;  /* This is used as a boolean value. */
        }
        else
        {
            encdecflag = 0;
            fprintf(stderr, "ERROR: Invalid optinal flag. Try any of the below said format \n");
            fprintf(stderr, "USAGE: lsb_steg -e secret.txt image.bmp encrypted.bmp \n");
            fprintf(stderr, "USAGE: lsb_steg -e secret.txt image.bmp \n");
            fprintf(stderr, "USAGE: ./lsb_steg -d encrpted.bmp message.txt\n");
            fprintf(stderr, "USAGE: ./lsb_steg -d encrpted.bmp \n");
            exit(1);
        }
    }

    /* Things to do while Encrypting */
    if (encdecflag == 1)
    {
        if (argc == 3)
        {
            txtfileName = argv[2];
        }
        else if (argc == 4)
        {
            txtfileName = argv[2];
            bmpfileName = argv[3];
        }
        else
        {
            fprintf(stderr, "ERROR: No file is passed. Try any of the below said format \n");
            fprintf(stderr, "USAGE: lsb_steg -e secret.txt image.bmp encrypted.bmp \n");
            fprintf(stderr, "USAGE: lsb_steg -e secret.txt image.bmp \n");
            exit(1);
        }
        
        /* check for File Existance */
        secretfile = fopen(txtfileName,"r");
        if (NULL == secretfile)
        {
            fprintf(stderr, "ERROR: .txt file is not readable\n");
            exit(1);
            //File not found
        }
        else
        {
            // file exists
            printf( ".txt file is readable\n");
            
            /* Get the size of the file and seek back to 
             *  beginning of the file for next use 
             */
            fseek(secretfile, 0L, SEEK_END);
            txtFileSize = ftell(secretfile);
            fseek(secretfile, 0L, SEEK_SET);
            printf( "fsecret file size: %d\n", txtFileSize);
            
            
            /* check if bmp File is given through command line or not */
            if (bmpfileName == NULL)
            {
                printf("No .bmp file is given, taking default.bmp which should be in the current directory \n");
                /* default.bmp should be in the current directory */
                bmpfileName = "default.bmp";
            }
            
            /* check for File Existance */
            bmpfile = fopen(bmpfileName,"r+");
            if (NULL == bmpfile)
            {
                fprintf(stderr, "ERROR: .bmp file is not readable\n");
                fclose(secretfile);
                exit(1);
                //File not found
            }
            else
            {
                // file exists
                printf( ".bmp file is readable\n");
                /* Get the size of the file and seek back to
                 *  beginning of the file for next use
                 */
                fseek(bmpfile, 0L, SEEK_END);
                bmpFileSize = ftell(bmpfile);
                fseek(bmpfile, 0L, SEEK_SET);
                printf( "bmpFileSize file size: %d\n", bmpFileSize);
                
                /* Check for Size Compatibility */
                if ( ((bmpFileSize - 54) - (8 * txtFileSize)) < 1)
                {
                    fprintf(stderr, "ERROR: .bmp file is not of enough size \n");
                    fclose(bmpfile);
                    fclose(secretfile);
                    exit(1);
                }
            }
        }
        
    }
    else if (encdecflag == 2)
    {
        if (argc == 3)
        {
            encryptbmpfileName = argv[2];
        }
        else if (argc == 4)
        {
            encryptbmpfileName = argv[2];
            txtfileName = argv[3];
        }
        else
        {
            fprintf(stderr, "ERROR: No file is passed.. Try any of the below said format \n");
            fprintf(stderr, "USAGE: ./lsb_steg -d encrpted.bmp message.txt\n");
            fprintf(stderr, "USAGE: ./lsb_steg -d encrpted.bmp \n");
            exit(1);
        }
        
        /* check for File Existance */
        encrptfile = fopen(encryptbmpfileName,"r");
        if (NULL == encrptfile)
        {
            fprintf(stderr, "ERROR: file is not readable\n");
            exit(1);
            //File not found
        }
        else
        {
            // file exists
            printf( "file is readable\n");
            fclose(encrptfile);
        }
        
    }
    
    fclose(bmpfile);
    fclose(secretfile);
    return 0;
}