/*
 * Filename: recursiveGrepEC.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: June 2nd, 2019
 * Sources of help: textbook, lecture notes, discussion notes, cse 30 website.
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/*
 * Function Name: recursiveGrepEC()
 * Function Prototype: int recursiveGrep( argInfo_t * info, const char * path );
 * Description: Recursively greps on path, which can refer to either a regular
 *             file or a directory.
 * Parameters: info - The struct containing the regex and flags.
 *             path - the path to recurse on .
 *
 * Side Effects: None.
 * Error Conditions: We can't stat the file.
 *                    
 * Return Value: -1 for error, else 0.
 */
int recursiveGrep( argInfo_t * info, const char * path ) {

  struct stat buffer;       // Create a struct stat to stat the file 
  int status = 0;          // Check the status of the stat 
  int is_stdin;           // Check if its coming from stdin 
  errno = 0;


  // Check if the path is from stdin 
  is_stdin = strcmp( path, STR_STDIN );

  if( is_stdin != 0 ) {

    status = stat( path, &buffer );

    // Check if we can stat the file 
    if( errno != 0 || status == -1 ) {
      fprintf( stderr, STR_ERR_OPEN_FILE, path, strerror(errno));
      return -1;
    }

    // Check if the file is a directory 
    if( S_ISDIR(buffer.st_mode ) != 0  ) {
      recursiveGrepDir( info, path );
      return 0;
    } 

    // Check if the count flag has been set 
    if( (info->flags & ARG_C_FLAG) == ARG_C_FLAG ) {
      count( info, path );
    }
    // Search the path for the specified pattern 
    else {
      search( info, path );
    }
    return 0;
  }

  // Check if the count flag was set 
  if( (info->flags & ARG_C_FLAG) == ARG_C_FLAG ) {
    count( info, path );
  }
  // Search the path for the pattern
  else {
    search( info, path );
  }

  return 0;
}
