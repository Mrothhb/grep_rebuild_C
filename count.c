/*
 * Filename: count.c
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
 * Function Name: count()
 * Function Prototype: int count( const argInfo_t * info, const char * 
 *                      filename );
 * Description: Counts the number of lines in filename that match the pattern 
 *              found in info. 
 * Parameters: info - The struct containing the regex and flags.
 *             filename - the file to search.
 *
 * Side Effects: The count of the matching lines are printed to stdout.
 * Error Conditions: The file could not be opened.
 *                    
 * Return Value: -1 for error, else 0.
 */
int count( const argInfo_t * info, const char * filename ) {

  FILE * fp;
  char * str; 
  int count = 0;

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

      // Collect the count of the lines that match
      if( lineShouldBePrinted( str , info ) == 1 ){ 

        ++count;
      }
    }  
  }

  // Check for multi files and -n flag 
  if( (info->flags & ARG_MULTI_FILE ) == ARG_MULTI_FILE ) {
    fprintf( stdout, STR_FILENAME, filename );
  }

  // print the count to stdout, free the string
  fprintf( stdout, STR_COUNT, count );
  free( str );

  // Close the file and exit 
  fclose( fp );
  return 0;
}
