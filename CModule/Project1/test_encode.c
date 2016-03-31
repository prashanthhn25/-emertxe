#include <stdio.h>
#include "encode.c"
#include "types.h"

int main(int argc, char **argv)
{
    EncodeInfo encInfo;
    
    // To store size of image and secret file
    uint src_img_size;
    
    // Fill with sample filenames
    encInfo.src_image_fname = "beautiful.bmp";
    encInfo.secret_fname = "secret.txt";
    encInfo.stego_image_fname = "stego_img.bmp";
    
    // Test argument
    if ((argc < 3))
    {
        print_usage_error("Invalid Arguments");
        return 1;
    }
    
    //Test check_operation_type and read_and_validate_encode_args
    if (read_and_validate_encode_args(argv, &encInfo) == e_failure)
    {
        print_usage_error("Invalid Entry. Not Supported");
        return 1;
    }
    
    
    // Test open_files
    if (open_files(&encInfo) == e_failure)
    {
        printf("ERROR: %s function failed\n", "open_files" );
        return 1;
    }
    
    if (check_operation_type(argv) == e_encode)
    {

        // Test get_image_size_for_bmp
        encInfo.image_capacity = get_image_size_for_bmp(encInfo.fptr_src_image);
        //printf("INFO: Image size = %u\n", encInfo.image_capacity);
    
        // Test get_file_size
        encInfo.size_secret_file = get_file_size(encInfo.fptr_secret);
        //printf("INFO: secret  size = %ld\n", encInfo.size_secret_file);
    
        //Test check_capacity
        if (check_capacity(&encInfo) == e_failure)
        {
            printf("%s has less capacity: %u.\n", encInfo.src_image_fname, encInfo.image_capacity );
            fclose(encInfo.fptr_src_image);
            fclose(encInfo.fptr_secret);
            fclose(encInfo.fptr_stego_image);
            return 1;
        }
    
        //Test copy_bmp_header
        if (copy_bmp_header(encInfo.fptr_src_image, encInfo.fptr_stego_image) == e_failure)
        {
            printf("Did not copy\n");
            return 1;
        }
    
        //Test encode_secret_file_size
        if ( encode_secret_file_size(encInfo.size_secret_file, &encInfo) == e_failure)
        {
            printf("Did not encode secret file size.\n");
            return 1;
        }
    
        //Test encode_secret_file_data [includes null too]
        if ( encode_secret_file_data(&encInfo) == e_failure)
        {
            printf("Did not encode secret file data.\n");
            return 1;
        }
    
        //Test copy_remaining_img_data [includes null too]
        if ( copy_remaining_img_data(encInfo.fptr_src_image, encInfo.fptr_stego_image)  == e_failure)
        {
            printf("Did not encode rest of the data.\n");
            return 1;
        }
    }
    else if (check_operation_type(argv) == e_decode)
    {

    }
    return 0;
}