/*
 * Filename: openFile.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: June 2nd, 2019
 * Sources of help: textbook, lecture notes, discussion notes, cse 30 website.
 */

#include <errno.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


/*
 * Function Name: openFile()
 * Function Prototype: FILE * openFile( const char * filename ); 
 * Description: Opens filename so that it can be read. If the filename is "-", 
 *              redirect to stdin instead.  
 * Parameters:  filename - the file to be opened.
 *
 * Side Effects: The file is opened and a pointer to the file is returned.
 * Error Conditions: Can't stat file, file is a directory, file cannot be open.
 *                    
 * Return Value: NULL if error, else the file pointer.
 */
FILE * openFile( const char * filename ) {

  FILE * fp;      // File pointer to the filename parameter after opening file  

  // Check if reading from stdin 
  if( strcmp(filename , STR_STDIN ) == 0 ) {
    return stdin;
  }

  struct stat buffer;       // The stat struct to check the filename       
  int status;              // the success of stat()
  errno = 0;

  // Stat the file 
  status =  stat( filename, &buffer ); 

  // Check if we can stat the file 
  if( errno != 0 || status == -1 ) {
    fprintf( stderr, STR_ERR_OPEN_FILE, filename, strerror(errno));
    return NULL;
  }

  // Check if the file is a directory 
  if( S_ISDIR(buffer.st_mode ) != 0  ) {
    fprintf( stderr, STR_ERR_OPEN_FILE, filename, strerror(EISDIR));
    return NULL;
  }

  // Open the file 
  fp = fopen( filename, STR_OPEN_READ );

  // Check if the file could not be opened 
  if( errno != 0 || fp == NULL) {
    fprintf( stderr, STR_ERR_OPEN_FILE, filename, strerror(errno));
    return NULL;
  }

  // Return the opened file 
  return fp;  
}
