#ifndef _STR_TOOLS_H_
#define _STR_TOOLS_H_

#include "comm_types.h"
#include "headers.h"

//---------------------------------------------------------
// str
//---------------------------------------------------------
const char*	StrPrintf( const char* fmt, ... );
bool		StrEqual( const char* s1, const char *s2 );
byte		StrHash( const char* str );
const char*	StrTabs( int tabCount );
void		StrReplace( char *str, char chFind, char chReplace );
void		StrCopy( char *str, const char *from, int maxSize = 0 );
int			StrLineCount( const char* str, int len );
const char* StrSkipChars( const char* str, const char* charSet );	//������� ������ ��������� ������� �������� ��� � ������ charSet
bool		StrCheck( const char* str );
void		StrCharReplace( char *str, char oldCh, char newCh );

//digitCount - ����� ���� (����������� ������), 89 -> (0089), ���� �������� 4
const char*	StrNumber( int num, int digitCount );

/* ���������� ��������� �� 
*/
char*		StrToken( const char *strToken, const char *strDelimit, int &resLength );

#endif
 