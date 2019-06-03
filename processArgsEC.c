/*
 * Filename: processArgsEC.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 29th, 2019
 * Sources of help: textbook, lecture notes, discussion notes, cse 30 website.
 */

#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <getopt.h>
#include "pa4.h"
#include <stdlib.h>

/**
 * The struct for holding the options that will be parsed from the command
 * line. 
 */
static struct option options[] = {
  { PATTERN_LONG, required_argument, NULL, PATTERN_FLAG },
  { IGNORE_CASE_LONG, no_argument, NULL, IGNORE_CASE_FLAG },
  { INVERT_MATCH_LONG, no_argument, NULL, INVERT_MATCH_FLAG },
  { COUNT_LONG, no_argument, NULL, COUNT_FLAG },
  { LINE_NUMBER_LONG, no_argument, NULL, LINE_NUMBER_FLAG },
  { HELP_LONG, no_argument, NULL, HELP_FLAG },
  { RECURSIVE_LONG, no_argument, NULL, RECURSIVE_FLAG },
  { 0 , 0, 0 ,0 }
};

/*
 * Function Name: processArgsEC()
 * Function Prototype:  int processArgs( argInfo_t * info, int argc, char 
 *                         * argv[] );
 * Description: Populates info with a regex pattern and a bit pattern 
 *              representing which flags were set in the command line arguments.
 * Parameters:  info -  the argInfor_t struct.
 *              argc -  the argument count.
 *              argv[] - the array of string arguments.
 *
 * Side Effects: The 
 * Error Conditions: None.
 *                    
 * Return Value: ARG_PARSING_ERROR if error occurred, parsing flags, REGEX_ERROR
 *               otherwise 0.
 */
int processArgs( argInfo_t * info, int argc, char * argv[] ) {

  info->flags = 0;                             // Set the flag to zero 
  const char * pattern;                       // The pattern to search 
  int opts;                                  // The options
  int rc = 0;                               // The success of the regcomp
  int pattern_flagged = 0;                 // The -e flag wasnt used 
  int cflags = REG_EXTENDED | REG_NOSUB;  // The clfags argument to regcomp

  // Parse the flags form the command line 
  while( ( opts = getopt_long( argc, argv, EC_SHORT_OPTS, options, NULL )) 
      != -1 ) {

    switch( opts ) {
      
      // Recursive flag detected 
      case RECURSIVE_FLAG:
        info->flags = info->flags | ARG_R_FLAG;
        break;
      // Regexp flag detected
      case PATTERN_FLAG:
        pattern = optarg;
        pattern_flagged = 1;
        break;
      // Ignore case flag detected   
      case IGNORE_CASE_FLAG:
        info->flags = info->flags | ARG_I_FLAG;
        cflags = cflags | REG_ICASE;
        break;
      // Invert match flag detected
      case INVERT_MATCH_FLAG:
        info->flags = info->flags | ARG_V_FLAG;
        break;
      // Count flag detected= 
      case COUNT_FLAG:
        info->flags = info->flags | ARG_C_FLAG;
        break;
      // Line number flag detected 
      case LINE_NUMBER_FLAG:
        info->flags = info->flags | ARG_N_FLAG;
        break;
      // Help flag detected 
      case HELP_FLAG:
        info->flags = info->flags | ARG_HELP_FLAG;
        return 0;
      // If the flag was not recognized 
      default:

        return ARG_PARSING_ERROR;
    }   
  }

  // No -e flag was detected  
  if( pattern_flagged != 1 ) {

    // If there is no pattern in the argument 
    if( argc <= optind  ){
      return ARG_PARSING_ERROR;
    }  
    // use the argument provided in the command line 
    pattern = argv[optind];
    ++optind;
  }

  // Check for multiple files on the command line 
  if( (argc - optind) > 1 ) {
    info->flags = info->flags | ARG_MULTI_FILE;
  }

  // Compile into a regex_t and store into first parameter 
  rc = regcomp( &(info->pattern), pattern, cflags );

  if( rc != 0 ) {
    return REGEX_ERROR;
  } 

  // Return success 
  return EXIT_SUCCESS;
}
