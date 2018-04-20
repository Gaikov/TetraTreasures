// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file EditString.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_EditString_H_
#define	_EditString_H_

#include "Str.h"

class nsEditString  
{
public:
	explicit nsEditString( int maxLen );

	void				SetMaxLen( int maxLen );
	void				SetLine( const char* line );
	inline const char*	GetLine() { return m_line; }
	inline int			GetCursorPos() { return m_cursorPos; }
	void				TypeChar( char ch );
		
	void				KeyHome();
	void				KeyEnd();
	void				KeyBackspace();
	void				KeyDelete();
	void				KeyLeft();
	void				KeyRight();

private:
	nsString	m_line;
	int			m_cursorPos;
	int			m_maxLen;
};

#endif	//_EditString_H_
