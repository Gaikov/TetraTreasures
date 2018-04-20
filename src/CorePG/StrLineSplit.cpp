// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file StrLineSplit.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "StrLineSplit.h"
#include "StrTools.h"

//---------------------------------------------------------
// nsStrLineSplit::nsStrLineSplit:
//---------------------------------------------------------
nsStrLineSplit::nsStrLineSplit( const char *text )
{
	SetText( text );
}

//---------------------------------------------------------
// nsStrLineSplit::SetText:
//---------------------------------------------------------
void nsStrLineSplit::SetText( const char *text )
{
	m_list.clear();

	while ( text && *text )
	{
		int len = strcspn( text, "\r\n" );
		strLineDesc_t	desc;
		desc.line = text;
		desc.length = len;

		m_list.push_back( desc );
		if ( len >= (int)strlen( text ) ) return;

		text = StrSkipChars( text + len, "\r\n" );
	}
}

//---------------------------------------------------------
// nsStrLineSplit::GetLine:
//---------------------------------------------------------
const strLineDesc_t* nsStrLineSplit::GetLine( int i )
{
	if ( i < 0 || i >= (int)m_list.size() ) return 0;
	return &m_list[i];
}