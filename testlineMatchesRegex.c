/*
 * Filename: testlineMatchesRegex.c
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
 * Unit Test for lineMatchesRegex.s
 *
 */

void testlineMatchesRegex() {
  
 const char * line1 = " not a match";
 const char * line2 = " !no a match ";

 const char * line3 = " match ";
 const char * line4 = "match";

 const char * line5 = "match";
 const char * line6 = "MATCH";

 const char * line7 = "[a-z]*";
 const char * line8 = "-'`";

 const char * line9 = "abc*";
 const char * line10 = "abcd";


 int cflags = REG_EXTENDED | REG_NOSUB;
 argInfo_t info = { 0 };  
 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), "pattern", cflags ); 
 TEST( lineMatchesRegex( &info.pattern, "pattern") == 1 );

 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), "pattern ejkrhejk", cflags ); 
 TEST( lineMatchesRegex( &info.pattern, "pattern") == 0 );

 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), "string test", cflags ); 
 TEST( lineMatchesRegex( &info.pattern, "string test") == 1 );

 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), line1, cflags ); 
 TEST( lineMatchesRegex( &info.pattern, line2) == 0);

 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), line3, cflags ); 
 TEST( lineMatchesRegex( &info.pattern, line4) == 0);
 
 cflags = cflags | REG_ICASE;
 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), line5, cflags ); 
 TEST( lineMatchesRegex( &info.pattern, line6) == 1);

 cflags =  REG_EXTENDED | REG_NOSUB;
 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), line7, cflags ); 
 TEST( lineMatchesRegex( &info.pattern, line8) == 1);


 cflags =  REG_EXTENDED | REG_NOSUB;
 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), line9, cflags ); 
 TEST( lineMatchesRegex( &info.pattern, line10) == 1);
}

int main( void ) {
  
  fprintf( stderr, "Running tests for lineMatchesRegex.s...\n" );
  testlineMatchesRegex();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
