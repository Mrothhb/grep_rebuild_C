/*
 * Filename: testlineShouldBePrintedc
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: TODO
 * Sources of help: text book, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include <regex.h>
#include "pa4.h"
#include "test.h"
#include <string.h>

/*
 * Unit Test for lineShouldBePrinted.s
 *
 */

void testlineShouldBePrinted() {
 
 argInfo_t info = { 0 };

 int cflags = REG_EXTENDED | REG_NOSUB;

 const char * line1 = "test";
 const char * line2 = "test";
  
 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), line1, cflags ); 
 TEST( lineShouldBePrinted(line1, &info) == 1);

 
 memset( &info, 0, sizeof(argInfo_t) );
 info.flags = 0x4;
 regcomp( &(info.pattern), line1, cflags ); 
 TEST( lineShouldBePrinted(line1, &info) == 0);



}

int main( void ) {
  
  fprintf( stderr, "Running tests for lineShouldBePrinted.c...\n" );
  testlineShouldBePrinted();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
