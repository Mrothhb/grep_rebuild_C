/*
 * Filename: recursiveGrepDirEC.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: June 2nd, 2019
 * Sources of help: textbook, lecture notes, discussion notes, cse 30 website.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

/*
 * Function Name: recursiveGrepDirEC()
 * Function Prototype: int recursiveGrepDir( argInfo_t * info, const char * 
 *                       dirpath );
 * Description: Recursively greps on dirpath, assuming dirpath refers to a 
 *              directory.
 * Parameters: info - The struct containing the regex and flags.
 *             dirpath - the path to recurse on.
 *
 * Side Effects: None.
 * Error Conditions: The directory could not be opened.
 *                    
 * Return Value: -1 for error, else 0.
 */
int recursiveGrepDir( argInfo_t * info, const char * dirpath ) {

  // Create a directory pointer      
  DIR *dir;
  struct dirent *dp;
  char path[MAX_PATH_LEN];

  // Set the multi file flag 
  info->flags = info->flags | ARG_MULTI_FILE;

  // Open the directory with the path     
  dir = opendir( dirpath );
  errno = 0;

  // Check if the directory could not be opened 
  if( dir == NULL || errno != 0 ) {
    fprintf( stderr, STR_ERR_OPEN_FILE, dirpath, strerror(EISDIR) );
    return -1;
  }

  // Recursively call grep on each file/directory within the directory 
  while( ( dp = readdir( dir )) != NULL ) {

    // Build the path for each file/dir within the directory 
    snprintf( path, MAX_PATH_LEN, STR_PATH_JOIN, dirpath, dp->d_name );

    // Exclude all the directories containing ".", ".." or starting with "."
    if( strcmp(dp->d_name , STR_CURR_DIR) == 0 || 
        strcmp(dp->d_name, STR_PARENT_DIR) == 0 || 
        strncmp( dp->d_name, STR_CURR_DIR, 1) == 0 ) {

      continue;
    }

    // Call grep on the path 
    recursiveGrep(info, path );  
  }

  // Close the directory and return 
  closedir( dir );
  return 0;
}
