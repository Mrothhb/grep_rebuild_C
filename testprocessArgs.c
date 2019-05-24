/*
 * Filename: testprocessArgs.c
 * Author: TODO
 * UserId: TODO
 * Date: TODO
 * Sources of help: TODO
 */

#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <getopt.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for processArgs.c
 *
 * int processArgs( argInfo_t * info, int argc, char * argv[] );
 *
 * Processes arguments passed into the executable.
 *
 * Returns
 *  - ARG_PARSING_ERROR on error parsing flags,
 *  - REGEX_ERROR if compiling the regular expression fails,
 *  - otherwise returns 0.
 */

void testprocessArgs() {
  argInfo_t info = { 0 };
  
  // -e flag
  memset( &info, 0, sizeof(argInfo_t) );
  int argc = 3;
  char * argv[] = { "prog", "-e", "abc*" };
  optind = 0;

  TEST( processArgs( &info, argc, argv ) == 0 );
  TEST( optind == 3 );

  // Multiple files
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 5;
  char * argv1[] = { "prog", "-e", "abc*", "file0", "file1" };
  optind = 0;

  TEST( processArgs( &info, argc, argv1 ) == 0 );
  TEST( info.flags == ARG_MULTI_FILE );
  TEST( optind == 3 );

  /*
   * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS!
   *
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */
}

int main( void ) {
  
  fprintf( stderr, "Running tests for processArgs.c...\n" );
  testprocessArgs();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
