/*
 * Filename: processArgs.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 29th, 2019
 * Sources of help: textbook, lecture notes, discussion notes, cse 30 website.
 */

#include <stdio.h>
#include <regex.h>
#include "pa4.h"

/*
 * Function Name: lineShouldBePrinted()
 * Function Prototype: int lineShouldBePrinted( const char * line, const 
 *                     argInfo_t * info ); 
 * Description: Checks if lineshould be printed in search(). 
 * Parameters:  line -  the line to print.
 *              info -  the info struct to search for the match.
 *
 * Side Effects: None.
 * Error Conditions: None.
 *                    
 * Return Value: 1 if the line should be printed, else 0.
 */
int lineShouldBePrinted( const char * line, const argInfo_t * info ) {

  // set the "boolean" for line match 
  int line_matches = lineMatchesRegex( &info->pattern, line );

  // Check if the -v flag has been set
  if ( (info->flags & ARG_V_FLAG) == ARG_V_FLAG ) {

    // Check if the line matches in the regexec
    if ( line_matches == 1 ) {

      return 0;
    } 

    // print lines that dont match 
    else {

      return 1;
    }
  } 

  // Check for matching lines when the -v flag is not set 
  else {

    if( line_matches == 1 ) {

      return 1;
    }

    // The line does not match and the -v flag was not set 
    else {

      return 0;
    }
  }
}
