/*
 * Filename: search.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: TODO
 * Sources of help: textbook, lecture notes, discussion notes, cse 30 website.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: search()
 * Function Prototype: int search( const argInfo_t * info, const char * 
 *                      filename );  
 * Description: Opens filenameand prints out all lines that match the regex 
 *                    pattern found in info.
 * Parameters: info - The struct containing the regex and flags.
 *             filename - the file to search.
 *
 * Side Effects: The mathcing lines are printed to stdout.
 * Error Conditions: The file could not be opened.
 *                    
 * Return Value: -1 for error, else 0.
 */
int search( const argInfo_t * info, const char * filename ) {

  FILE * fp;
  int line_num = 1;
  char * str; 

  // Open the file 
  fp = openFile( filename );

  // If the file was unsuccessfuly opened return -1
  if( fp == NULL ) {
    return -1;
  }

  // Continue to read the lines in the file until the terminate flag is set 
  while( RUNNING ) {

    // Get the next line in the file 
    str = readLine( fp );  

    if (str == NULL ) {
      free( str );
      break;
    }
    else {

      // Determine if the line should be printed to stdout 
      if( lineShouldBePrinted( str , info ) == 1 ){ 

        // Check for multi files and -n flag 
        if( (info->flags & ARG_MULTI_FILE ) == ARG_MULTI_FILE ) {
          fprintf( stdout, STR_FILENAME, filename );
        }

        if( (info->flags & ARG_N_FLAG ) == ARG_N_FLAG ) {
          fprintf( stdout, STR_LINENUM, line_num );
        }

        // print the line to stdout, free the string, and increment the linenum 
        fprintf( stdout, STR_LINE, str );
      }
    }
    // Keep track of the line number and free the allocated memory 
    ++line_num;
    free( str );
  }

  // Close the file and exit 
  fclose( fp );
  return 0;
}
