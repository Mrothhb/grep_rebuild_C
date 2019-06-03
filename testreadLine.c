/*
 * Filename: testreadLine.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: June 2nd, 2019
 * Sources of help: text book, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include <regex.h>
#include "pa4.h"
#include "test.h"
#include <string.h>

/*
 * Unit Test for readLine.s
 *
 */

void testreadLine() {
   
  FILE *fp;
  FILE *fp2;
  char * str;
  char * string = " NORMAL SIZED FILE WITH LEADING WHITESPACE ";
  const char * longstr = "thwejhtwetheuthwejrthejthkejrhfrklehtkljhtkjrehtkjew"
  "htklrehtlkjrwehkjlhtkjlerthrekjtherkljthwrekjthwkjrelhtwlkjehjthrekjwhtkjwre"
  "htjkrwehtkwjerhtrekjhtrkjwehtwlrekjhtlkwejtlkjwrehltwrekjhtwekjhtjewkhtkjrwe"
  "thrjwekhtrkjwehkjthjwekhrwejkhtwejkhtwjrekhtjkj";

  const char * empty = "";

  fp = fopen( "normal.txt", "r" );
  str = readLine( fp );
  TEST( strcmp( string, str ) == 0);
  fclose(fp);
  free( str );
 
  fp = fopen( "textempty.txt", "r");
  str = readLine( fp );
  TEST( strcmp(str, empty) == 0 );
  fclose(fp);
  free( str );

  fp = fopen( "longstring.txt", "r");
  str = readLine( fp );
  TEST( strcmp(str, longstr) == 0);
  fclose(fp);
  free( str );

  fp = fopen( "textempty.txt", "r");
  str = readLine( fp );
  TEST( strcmp(str, empty) == 0);
  fclose(fp);

  free( str );

 }

int main( void ) {
  
  fprintf( stderr, "Running tests for readLine.c...\n" );
  testreadLine();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
