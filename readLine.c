/*
 * Filename: readLine.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 29th, 2019
 * Sources of help: textbook, lecture notes, discussion notes, cse 30 website.
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <string.h>

/*
 * Function Name: readLine()
 * Function Prototype: char * readLine( FILE * inputFile ); 
 * Description: Reads a singleline from inputFile stopping at a newline 
 *              or when it hits the end-of-file (EOF).  
 * Parameters:  inputFile - The file to read input from.
 *
 * Side Effects: The file data is read one line at a time into a string.
 * Error Conditions: Reached EOF while strng is empty , or memory allocation 
 *                   fails.
 *                    
 * Return Value: NULL if any errors, or else pointer to null terminated string
 *               containing a line from the file.
 */
char * readLine( FILE * inputFile ) {

  char buffer[LINE_BUFFER_SIZE];              // Buffer from reading file input
  char * str = calloc( 1, sizeof( char ));    // Dynamically allocated empty str
  int end_loop = 0;                           // The condition to end the loop

  if( inputFile == NULL ){
    return NULL;
  }

  // Read each line in the file 
  while( RUNNING ) {

    // Read one line at a time, and exit once EOF is reached     
    if( fgets( buffer, LINE_BUFFER_SIZE, inputFile ) == NULL ){
      free ( str );
      return NULL;
    }  

    // Check for the newline character 
    char * pos = strchr( buffer, NEWLINE_CHAR );

    // set the null char to replace the newline char 
    if( pos != NULL ) {
      *pos = '\0';
      end_loop = 1;
    }

    // Get the length of the buffer 
    int str_len = strlen( str );

    // Allocate space for the buffer into the string 
    char * temp_str  = realloc( str, str_len + (LINE_BUFFER_SIZE)*sizeof(char));

    if( temp_str == NULL ) {
      // Free the pointer if the allocation failed 
      free( str );
      fprintf( stderr, STR_ERR_MEM_EXCEEDED );
      return NULL;
    }  

    // Concatenate the buffer onto the string 
    strncat(temp_str, buffer, str_len + (LINE_BUFFER_SIZE) );
    str = temp_str; 

    if( end_loop == 1 ) {
      break;
    }           
  } 

  // Check if the string is still NULL    
  if( str == NULL ) {
    free( str );
    return NULL;
  }
  
  // return the string 
  return str;

}
