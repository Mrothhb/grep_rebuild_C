/*
 * Filename: testprocessArgs.c
 * Author: Matt Roth
 * UserId: cs30xgs 
 * Date: May 29th, 2019
 * Sources of help: textbook, cse 30 website, lecture notes, discussion notes. 
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
  //int pattern = 0;
  
  // -e flag
  memset( &info, 0, sizeof(argInfo_t) );
 int argc = 7;
 char * argv[] = { "./mygrep","-i", "-e","pattern", "file", "-v", "-n"};
 optind = 0;

 TEST( processArgs( &info, argc, argv ) == 0 );
 TEST( info.flags == ( 0 | ARG_I_FLAG | ARG_V_FLAG | ARG_N_FLAG ));
 TEST( optind == 6 );

  // no flags 
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 3;
  char * argv1[] = { "./exe", "-e", "abc*" };
  optind = 0;
  
  TEST( processArgs( &info, argc, argv1 ) == 0 );
  TEST( info.flags != (ARG_MULTI_FILE));
  TEST( optind == 3 );

  memset( &info, 0, sizeof(argInfo_t) );
  argc = 8;
  char * argv2[] = { "./exe ", "-e", "pattern", "file1", "file2" ,"-i", "-v",
  "-c" };
  optind = 0;

  TEST( processArgs( &info, argc, argv2 ) == 0 );
  TEST( info.flags == (0 | ARG_I_FLAG | ARG_V_FLAG | ARG_C_FLAG 
  | ARG_MULTI_FILE) );  
  TEST( optind == 6 );

  memset( &info, 0, sizeof(argInfo_t) );
  argc = 2;
  char * argv3[] = { "./exe", "pattern"};
  optind = 0;

  TEST( processArgs( &info, argc, argv3 ) == 0 );
  TEST( optind == 2 );
  TEST( info.flags == (0) );  


  memset( &info, 0, sizeof(argInfo_t) );
  argc = 1;
  char * argv4[] = { "./exe"};
  optind = 0;

  TEST( processArgs( &info, argc, argv4 ) == -1 );

  
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 7;
  char * argv5[] = { "./exe","-e", "pattern", "-i", "-v", "-n", "-c"};
  optind = 0;
  TEST( processArgs( &info, argc, argv5 ) == 0 );
  TEST( info.flags == (ARG_N_FLAG | ARG_I_FLAG | ARG_V_FLAG | ARG_C_FLAG) );  
  TEST( optind == 7);

    
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 4;
  char * argv6[] = { "./exe","-k", "abc*", "file0"};
  optind = 0;

  TEST( processArgs( &info, argc, argv6 ) == -1 );
  TEST( info.flags == 0);
  TEST( optind == 2);

      
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 5;
  char * argv7[] = { "./exe","-k", "-a", "abc*", "file0"};
  optind = 0;

  TEST( processArgs( &info, argc, argv7 ) == -1 );
  TEST( info.flags == 0);
  TEST( optind == 2);

  memset( &info, 0, sizeof(argInfo_t) );
  argc = 3;
  char * argv8[] = {"./mygrep", "file", "-e"};
  optind = 0;

  TEST( processArgs( &info, argc, argv8 ) == -1 );
  TEST( info.flags == 0 );
  TEST( optind == 3 );
  
}

int main( void ) {
  
  fprintf( stderr, "Running tests for processArgs.c...\n" );
  testprocessArgs();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
