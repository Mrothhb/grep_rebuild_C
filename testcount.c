/*
 * Filename: testseacrh.c
 * Author: Matt Roth
 * UserId: cs30xgs 
 * Date: June 19th, 2019
 * Sources of help: textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <getopt.h>
#include "pa4.h"
#include "test.h"

/*
 * Unit Test for search.c
 *
 */

void testsearch() {
  argInfo_t info = { 0 };
  int cflags = REG_EXTENDED | REG_NOSUB;
 
  memset( &info, 0, sizeof(argInfo_t) );
  regcomp( &(info.pattern), "start", cflags ); 
  info.flags = ARG_MULTI_FILE;
  count( &info, "sample.txt" ); 
  count ( &info, "secret.txt");

}

int main( void ) {

  fprintf( stderr, "Running tests for search.c...\n" );
  testsearch();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
