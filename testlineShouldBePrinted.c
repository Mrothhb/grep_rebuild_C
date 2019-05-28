/*
 * Filename: testlineShouldBePrinted.c
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

 const char * line3 = "nananana ";
 const char * line4 = " anana ana ";

 const char * line5 = " ANANA ANA ";

  
 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), line1, cflags ); 
 TEST( lineShouldBePrinted(line1, &info) == 1);

 
 memset( &info, 0, sizeof(argInfo_t) );
 info.flags = 0x4;
 regcomp( &(info.pattern), line1, cflags ); 
 TEST( lineShouldBePrinted(line1, &info) == 0);

  
 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), line3 ,cflags ); 
 TEST( lineShouldBePrinted(line4, &info) == 0);
  
 memset( &info, 0, sizeof(argInfo_t) );
 info.flags = 0x4;
 regcomp( &(info.pattern), line3 ,cflags ); 
 TEST( lineShouldBePrinted(line4, &info) == 1);


 memset( &info, 0, sizeof(argInfo_t) );
 info.flags = 0x4;
 regcomp( &(info.pattern), line4 ,cflags ); 
 TEST( lineShouldBePrinted(line4, &info) == 0);

 memset( &info, 0, sizeof(argInfo_t) );
 regcomp( &(info.pattern), line4 ,cflags ); 
 TEST( lineShouldBePrinted(line4, &info) == 1);

 memset( &info, 0, sizeof(argInfo_t) );
 cflags = cflags | REG_ICASE;
 regcomp( &(info.pattern), line4, cflags ); 
 TEST( lineShouldBePrinted(line5, &info) == 1);

 memset( &info, 0, sizeof(argInfo_t) );
 cflags = cflags | REG_ICASE;
 info.flags = info.flags | ARG_I_FLAG | ARG_V_FLAG;
 regcomp( &(info.pattern), line4, cflags ); 
 TEST( lineShouldBePrinted(line5, &info) == 0);

 memset( &info, 0, sizeof(argInfo_t) );
 cflags = cflags | REG_ICASE;
 info.flags = info.flags | ARG_I_FLAG;
 regcomp( &(info.pattern), line4, cflags ); 
 TEST( lineShouldBePrinted(line5, &info) == 1);
}

int main( void ) {
  
  fprintf( stderr, "Running tests for lineShouldBePrinted.c...\n" );
  testlineShouldBePrinted();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
