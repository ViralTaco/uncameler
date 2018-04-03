/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef char* string;

int main(int argc, char *argv[]) 
{
        if (argc == 1)
        {
                fputs("ERROR: No file to decamelize", stderr);
                exit(EXIT_FAILURE);
        }
        
        const string file_to_decamelize_location = argv[1];
        
        FILE *file_ptr;
        
        if ((file_ptr = fopen(file_to_decamelize_location, "r")) == NULL)
        {
                fputs("ERROR: Couldn't read the file", stderr);
                exit(EXIT_FAILURE);
        }
        
        FILE *new_file_ptr;
        
        if ((new_file_ptr = fopen("./uncameled.txt", "w")) == NULL)
        {
                fputs("ERROR: Couldn't create file", stderr);
                exit(EXIT_FAILURE);
        }
        
        bool is_ok = true;
        int c = 0;
        int temp = 0;
        do 
        {
                c = fgetc(file_ptr);
                if (c == '\"') is_ok = (is_ok) ? false : true;
                
                if (islower(temp) && isupper(c) && is_ok)
                {
                        fputc('_', new_file_ptr);
                        fputc(tolower(c), new_file_ptr);
                }
                else fputc(c, new_file_ptr);
                
                temp = c;
        } while (c != EOF);
        
        fclose(file_ptr); fclose(new_file_ptr);
}
