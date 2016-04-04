#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "encode.h"
#include "types.h"

/* Function Definitions */

/* Get error message 
 * Input: Error message
 * Description: prints Usage format and error message
 */
 
 //! Byte swap int
uint swap_int32( uint val )
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | ((val >> 16) & 0xFFFF);
}
 
void print_usage_error(char * message)
{
    fprintf(stderr, "ERROR: %s \n", message);
    fprintf(stderr, "USAGE: lsb_steg -e secret.txt image.bmp encrypted.bmp \n");
    fprintf(stderr, "USAGE: lsb_steg -e secret.txt image.bmp \n");
    fprintf(stderr, "USAGE: ./lsb_steg -d encrpted.bmp message.txt\n");
    fprintf(stderr, "USAGE: ./lsb_steg -d encrpted.bmp \n");
}

void print_file_error(char * message)
{
    perror("fopen");
    fprintf(stderr, "ERROR: Unable to open file %s\n", message);
}


/* Check operation type
 * Input: argv[] from command line 
 * Output: OperationType for encoding or decoding
 * Description: check for valid optional argument and 
 *  return the appropriate enum values
 */
OperationType check_operation_type(char *argv[])
{
    if (strcmp(argv[1], "-e") == 0)
    {
        //return e_encode
        return e_encode;
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        //return e_decode
        return e_decode;
    }
    // Neither return e_unsupported
    return e_unsupported;
}

/* Read and validate Encode args from argv 
 * Input: argv[] from command line and EncodeInfo address
 * Output: Status success or failure
 * Description: check for valid optional argument and
 *  read the appropriate argv values for filenames
 */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    //Test check_operation_type
    if (check_operation_type(argv) == e_encode)
    {
        // take this as secret file
        encInfo->secret_fname = argv[2];
        if (argv[3] != NULL)
        {
            // take 3rd arg as bmp file if present
            encInfo->src_image_fname = argv[3];
        }
        // No failure return e_success
        return e_success;
    }
    else if (check_operation_type(argv) == e_decode)
    {
        // take this as encrypted file
        encInfo->stego_image_fname = argv[2];
        if (argv[3] != NULL)
        {
            // take 3rd arg as secret message file if present
            encInfo->secret_fname = argv[3];
        }
        // No failure return e_success
        return e_success;
        
    }
    else if (check_operation_type(argv) == e_unsupported)
    {
        return e_failure;
    }
    
    return e_failure;
}


/* Get file size
 * Input: Secret file ptr
 * Output: uint size
 * Description: In file.txt, go to the EOF and seek the poistion
 * and save, once done, reset the position to 0 and return the 
 * saved value which gives the size of the file
 */
uint get_file_size(FILE *fptr)
{
    uint file_size;
    
    // Seek to nth byte
    fseek(fptr, 0L, SEEK_END);
    // Save the current position value
    file_size = ftell(fptr);
    // Seek back to 0th byte
    fseek(fptr, 0L, SEEK_SET);
    
    //Return the size
    return file_size;
}

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    /*
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
     */
    
    uint image_size;
    
    // Seek to nth byte
    fseek(fptr_image, 0L, SEEK_END);
    // Save the current position value
    image_size = ftell(fptr_image);
    // Seek back to 0th byte
    fseek(fptr_image, 0L, SEEK_SET);
    
    //Return the size
    return image_size;
    
}

/* check capacity */
Status check_capacity(EncodeInfo *encInfo)
{
    /* Check for Size Compatibility */
    if ( ((((long int)encInfo->image_capacity) - 54) - (8 * encInfo->size_secret_file)) < 1)
    {
        return e_failure;
    }
    
    return e_success;
}


/* Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    //Do Error handling
    if (NULL == encInfo->fptr_src_image)
    {
        print_file_error(encInfo->src_image_fname);
    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    //Do Error handling
    if (NULL == encInfo->fptr_secret)
    {
        print_file_error(encInfo->secret_fname);
    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    //Do Error handling
    if (NULL == encInfo->fptr_stego_image)
    {
        print_file_error(encInfo->stego_image_fname);
    	return e_failure;
    }

    // No failure return e_success
    return e_success;

}

/* Copy bmp image header */
Status copy_bmp_header(FILE * fptr_src_image, FILE *fptr_dest_image)
{
    char image_header_data[55];
    int readptr, writeptr, i;
    
    /* To read exactly 54 bytes that contain header info */
    if ((readptr = fread(image_header_data, 1, 54, fptr_src_image)) != 54)
    {
        if (ferror(fptr_src_image) != 0)
        {
            fprintf(stderr, "Reading error. \n" );
            clearerr(fptr_src_image);
            return e_failure;
        }
    
    }
        
    /* If failed to write what is read into dest header */
    if ((writeptr = fwrite(image_header_data, 1, readptr, fptr_dest_image)) != readptr)
    {
        return e_failure;
    }
    
    return e_success;
}

/* Encode secret file size */
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{

    char MSBbits[32] = {0};
    int i, j, readptr, writeptr, iterptr, temp;
    
    /* MSB is in reverse order */
    for (i = 0; i < 32; i++)
    {
       // file_size & 0x00000001;
        if( (file_size & 0x00000001) == 0)
        {
            MSBbits[i] = '0';
        }
        else if( (file_size & 0x00000001) == 1)
        {
            MSBbits[i] = '1';
        }
        file_size >>= 1;
    }
    MSBbits[i] = '\0';
    
    //reverse string to get the MSBs in order
    for (i = 0, j = strlen(MSBbits)-1; i < j; i++, j--) {
        temp = MSBbits[i];
        MSBbits[i] = MSBbits[j];
        MSBbits[j] = temp;
    }
    
    //printf("%s", MSBbits);
    //printf("\n");
    
    // Seek to 55th byte and onward
    fseek(encInfo->fptr_src_image, 55L, SEEK_SET);
    // Seek to 55th byte and onward
    fseek(encInfo->fptr_stego_image, 55L, SEEK_SET);
    
    iterptr = ftell(encInfo->fptr_src_image);
   
    i = 1;
    // Encode the next 32 Image data into buffer for size
    while(iterptr < 87)
    {
        //printf("%d : ", iterptr);
        
        /* read byte by byte */
        if ((readptr = fread( encInfo->image_data, 1, 1, encInfo->fptr_src_image)) != 1)
        {
            if (ferror(encInfo->fptr_src_image) != 0)
            {
                fprintf(stderr, "Reading error. \n" );
                clearerr(encInfo->fptr_src_image);
                return e_failure;
            }
        }
       
        //fetched one byte successfully, so now check for encoding
        
        if(encode_byte_tolsb(MSBbits[i], encInfo->image_data) == e_failure)
        {
            fprintf(stderr, "Encoding error. \n" );
            return e_failure;
        }
    
        //encoded data saved in image_buffer is written to stegfile
        if((writeptr = fwrite(encInfo->image_data, 1, 1, encInfo->fptr_stego_image)) != 1)
        {
            fprintf(stderr,"write file error.\n");
            return e_failure;
        }
       
        i++;
        iterptr++;
    }
    
    return e_success;
}

/* Encode a byte into LSB of image data array */
Status encode_byte_tolsb(char data, char *image_buffer)
{
    //set LSB of the image_buffer with data and
    *image_buffer = ((*image_buffer & ~0x01) | (data & 0x01)) ;
    return e_success;
}

/* Encode secret file data*/
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    MsbMap msbtemp, tempValues;
    
    int readsecretptr, readptr, writeptr, i;
    char tempdata, mask;
    char *tempMsb;	

    
    // Seek to 0th byte and onward for secret file
    fseek(encInfo->fptr_secret, 0L, SEEK_SET);
    // Seek to 87th byte and onward for image file
    fseek(encInfo->fptr_src_image, 86L, SEEK_SET);
	//fseek(encInfo->fptr_src_image, 0L, SEEK_CUR);
	//printf(" %ld:", ftell(encInfo->fptr_src_image));
    // Seek to 87th byte and onward for steg file
    fseek(encInfo->fptr_stego_image, 86L, SEEK_SET);
    //fseek(encInfo->fptr_stego_image, 0L, SEEK_CUR);
        //printf(" %ld:", ftell(encInfo->fptr_src_image));


    /* Do till EOF for secret file is reached */

    while(feof(encInfo->fptr_secret) == '\0')
    {
        //Read 1 byte from secret file to secretdata buffer
        if((readsecretptr = fread(encInfo->secret_data, 1, 1, encInfo->fptr_secret))!= 1)
        {
            if(ferror(encInfo->fptr_secret)!=0)
            {
                fprintf(stderr,"read file error.\n");
                clearerr(encInfo->fptr_secret);
                return e_failure;
            }
        
        }
    
        //Get the MSBs in MSBbit for that secret data
        tempdata = *encInfo->secret_data;
	msbtemp.MSB_BYTE = *encInfo->secret_data;

	/* Reverse MSB and save */
	tempValues.bitaccess.BIT0 = msbtemp.bitaccess.BIT7;
	tempValues.bitaccess.BIT1 = msbtemp.bitaccess.BIT6; 
	tempValues.bitaccess.BIT2 = msbtemp.bitaccess.BIT5; 
	tempValues.bitaccess.BIT3 = msbtemp.bitaccess.BIT4; 
	tempValues.bitaccess.BIT4 = msbtemp.bitaccess.BIT3;
	tempValues.bitaccess.BIT5 = msbtemp.bitaccess.BIT2;
	tempValues.bitaccess.BIT6 = msbtemp.bitaccess.BIT1;
	tempValues.bitaccess.BIT7 = msbtemp.bitaccess.BIT0 ; 
	
	//printf("%d:%#x  = %#x\n", i, msbtemp.MSB_BYTE , tempValues.MSB_BYTE  );
		

	//printf("bitaccess.BIT7 = %#x\n", msbtemp.bitaccess.BIT7);
	//printf("\n");

	//read image byte and MSBbit and Encode for 8 bits
	//printf("\n ");
        for (i = 0; i < 8; i++)
        {
		
		// read byte by byte starting from 55th in image
            if ((readptr = fread( encInfo->image_data, 1, 1, encInfo->fptr_src_image)) != 1)
            {
                if (ferror(encInfo->fptr_src_image) != 0)
                {
                    fprintf(stderr, "Reading error. \n" );
                    clearerr(encInfo->fptr_src_image);
                    return e_failure;
                }
            }
		
		// Get the MSB value in mask
		mask = tempValues.MSB_BYTE & 0x01;
		//printf("%x ", mask);
	
	    //Only MSb should be used for encoding	

	    //fetched one byte successfully, so now check for encoding
             if(encode_byte_tolsb(mask, encInfo->image_data) == e_failure)
            {
                fprintf(stderr, "Encoding error. \n" );
                return e_failure;
            }
        		
	    //encoded data saved in image_buffer is written to stegfile
        
            if((writeptr = fwrite(encInfo->image_data, 1, 1, encInfo->fptr_stego_image)) != 1)
            {
                fprintf(stderr,"write file error.\n");
                return e_failure;
            }
	

	tempValues.MSB_BYTE >>= 1;
	}
	/* Do this eight times */
    
    }
    return e_success;
}


/* Copy remaining image bytes from src to stego image after encoding */
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    
    int readptr, writeptr, i;
    char image_remaining_data[MAX_IMAGE_BUF_SIZE];
    
    //get the current cursor value
    fseek(fptr_src, 0L, SEEK_CUR);
    //printf("%ld \n", ftell(fptr_src));
    
    
    while(feof(fptr_src)==0)
    {
        
        // To read remaining data till end
        if ((readptr = fread( image_remaining_data, 1, MAX_IMAGE_BUF_SIZE, fptr_src)) != MAX_IMAGE_BUF_SIZE)
        {
            if (ferror(fptr_src) != 0)
            {
                fprintf(stderr, "Reading error. \n" );
                clearerr(fptr_src);
                return e_failure;
            }
        
        }
    
        // If failed to write what is read into dest header
        if ((writeptr = fwrite( image_remaining_data, 1, readptr, fptr_dest)) != readptr)
        {
            return e_failure;
        }
    }

    return e_success;
    
}

/* Decode secret file size */
Status decode_secret_file_size(FILE * fptr_stego_image, long *size_secret_file)
{
    int readptr, i, j, k, iterptr, tempnum, temp;
    char MSBbits[32] = {0};
    char tempdata;
    char file_size_data;
    
    // Seek to 55th byte and onward
    fseek(fptr_stego_image, 54L, SEEK_SET);
  
 
	//printf(" %ld:", ftell(fptr_stego_image));
    // Decode the next 32 Image data into buffer for size
    for(i = 0; i < 32 ;i++)
    {
         
        //printf(" %ld:", ftell(fptr_stego_image));
	/* To read byte by byte */
        if ((readptr = fread(&file_size_data, 1, 1, fptr_stego_image)) != 1)
        {
            if (ferror(fptr_stego_image) != 0)
            {
                fprintf(stderr, "Reading error. \n" );
                clearerr(fptr_stego_image);
                return e_failure;
            }
        }
	        
	//printf("%x ", file_size_data);

   
        // Now decode 
        if (decode_byte_fromlsb(&tempdata, &file_size_data) == e_failure)
	 {
            printf("Decoding of LSb failed.");
            return e_failure;
        }
        MSBbits[i] = tempdata;
   }
    MSBbits[i] = '\0';
    
    //printf("%s\n", MSBbits);
    //printf("\n");
    
    //reverse MSB
    for (i = 0, j = strlen(MSBbits)-1; i < j; i++, j--)
    {
        temp = MSBbits[i];
        MSBbits[i] = MSBbits[j];
        MSBbits[j] = temp;
    }
    
    tempnum = 0;
    //get integer value
    for (i = 0; i < 32; i++)
    {
        if (MSBbits[i] == '1')
        {
            tempnum += pow(2,i);
        }
    }
    *size_secret_file = tempnum;
    //printf("%d \n", tempnum);

    return e_success;
    
}

/* decode a byte into array from LSB of image data  */
Status decode_byte_fromlsb(char *data, char *image_data)
{
    //get LSB of the data and store in imagebuffer
    //printf("%d", (*image_data & 0x01));
    *data = (*image_data & 0x01);
    if ((*image_data & 0x01) == 0)
    {
        *data = '0';
    }
    else if ((*image_data & 0x01) == 1)
    {
        *data = '1';
    }
    
    return e_success;
}

/* Decode secret file data */
Status decode_secret_file_data(FILE * fptr_secret, FILE * fptr_stego_image, long size_secret_file)
{
	
    int readptr, writeptr, i, j;

    char tempdata, msbdata, msbdata2;
    char file_size_data;
    
    //get the current cursor value
    fseek(fptr_stego_image, 0L, SEEK_CUR);
	
    //set to starting position of secret file
    fseek(fptr_secret, 0L, SEEK_SET);
    

    // Decode the next 32 Image data into buffer for size
    for(i = 0; i < size_secret_file; i++)
    {
        
        //for every 8 bytes we get one byte of data
        for (j = 0; j < 8; j++)
        {
            /* To read byte by byte */
            if ((readptr = fread(&file_size_data, 1, 1, fptr_stego_image)) != 1)
            {
                if (ferror(fptr_stego_image) != 0)
                {
                    fprintf(stderr, "Reading error. \n" );
                    clearerr(fptr_stego_image);
                    return e_failure;
                }
            }
 
		// Now decode to get LSB 
		msbdata = file_size_data & 01;
		
		// Shift and or	
		 msbdata2 = (msbdata2 <<= 1) | msbdata;
	
           }	
		//printf("%c",  msbdata2  );
	
	
        //now that we have the correct byte, write to secret file
        // If failed to write what is read into dest header
        if ((writeptr = fwrite( &msbdata2, 1, 1, fptr_secret)) != 1)
        {
            return e_failure;
        }
      
    }
    
    return e_success;

}
