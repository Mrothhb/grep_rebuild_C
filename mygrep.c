/*
 * Filename: mygrep.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: June 2nd, 2019
 * Sources of help: Textbook, cse30 website, lecture notes, discussion notes.
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <string.h>
#include <getopt.h>

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: This is the main driver of your program. Its main tasks are to
 *              parse any flags and arguments that are passed in, and to run the
 *              functionality of the grepcommand.
 * Parameters: argc is the argument counter, argv is each argument from the 
 *             command line.  
 * Side Effects: Run the program for mygrep. 
 * Error Conditions: The arguments could not be processed, or the regular 
 *                   expression could not be parsed. 
 * Return Value: EXIT_SUCCESS on success, and EXIT_FAILURE on failure.    
 */
int main( int argc, char * argv[] ) {

  argInfo_t info;             // The info on the stack for the flags and regex
  int processArgs_success;   // The success of the function call to processArgs

  // Process and parse all the arguments and pattern data 
  processArgs_success = processArgs( &info, argc, argv );
  
  // Check for an argument parsing error 
  if( processArgs_success == ARG_PARSING_ERROR ) {
    fprintf( stderr, STR_SHORT_USAGE, argv[0], argv[0]);
    return EXIT_FAILURE;
  }

  // Check for an error in the expression
  if( processArgs_success == REGEX_ERROR ) {
    fprintf( stderr, STR_ERR_REGEX );
    return EXIT_FAILURE;
  }

  // Check for the help flag and print to stdout 
  if( (info.flags & ARG_HELP_FLAG ) == ARG_HELP_FLAG ) {
    fprintf( stdout, STR_USAGE, argv[0], argv[0]);
    return EXIT_SUCCESS;
  }

  // Check if the file name is missing, use stdin for args to count and search 
  if( !(( argc-optind ) > 0) ) {
    if( ( info.flags & ARG_C_FLAG ) == ARG_C_FLAG ) {
      count( &info, STR_STDIN );
    } 

    // Search the file with stdin  
    else {
      search( &info, STR_STDIN );
    }
  } 

  else {
    // Search of count for all the given filenames from the command line 
    while( argv[optind] != NULL ) {
      if( ( info.flags & ARG_C_FLAG ) == ARG_C_FLAG ) {
        count( &info, argv[optind] );
      } 

      // Search the filwe with the filename from command line 
      else {
        search( &info, argv[optind] );
      }
      // Keep track of the file names 
      ++optind; 
    }
  }

  // Free allocated memory 
  regfree( &info.pattern );
  return EXIT_SUCCESS;
}
