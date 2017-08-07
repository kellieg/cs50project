#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

int main (int argc, char *argv[])
{
    // ensure proper CL input
    if (argc != 2)
    {
        fprintf(stderr, "# of command line arguments != 2\n");
        return 1;
    }
    
    // create file pointer to source and check existence
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "File can not be opened.\n");
        return 2;
    }
    

    // create pointer to char array and check existence
    uint8_t  *copy_from_source = malloc(512);
    if (copy_from_source == NULL)
    {
        fprintf(stderr, "Pointer %s is not created.\n", copy_from_source);
        fclose(inptr);
        return 3;
    }
    
    // counter for # of jpeg files
    int n = 0;
    // char array for jpeg filenames
    char filename[8];
    
    // do-while loop for reading in from source as long as end is not reached (<512 bytes read in)
    while ( fread(copy_from_source, 512, 1, inptr) == 1 )   
    {
        // check if block of bytes is new jpeg file, then create new jpeg file and write to
        if ( copy_from_source[0] == 0xff &&
             copy_from_source[1] == 0xd8 &&
             copy_from_source[2] == 0xff &&
            (copy_from_source[3] & 0xf0) == 0xe0)
            
            {
                // create name new numbered jpeg file
                sprintf(filename, "%03i.jpg", n);
                // write to numbered jpeg file
                FILE *jpeg = fopen(filename, "w");
                    if (jpeg == NULL)
                    {
                        fprintf(stderr, "jpeg file can not be opened.\n");
                        return 4;
                    }
                fwrite(copy_from_source, 512, 1, jpeg);
                fclose(jpeg);
            
                // increase n for next time a new jpeg header is found
                n++;
            }
            
        // else add data to existing, last created jpeg file
        else
            {
                FILE *jpeg_add = fopen(filename, "a");
                fwrite(copy_from_source, 512, 1, jpeg_add);
                fclose(jpeg_add);
            }
    }
    free(copy_from_source);

    return 0;
}