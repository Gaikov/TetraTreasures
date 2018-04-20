// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file StrLineSplit.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_StrLineSplit_H_
#define	_StrLineSplit_H_

#include <vector>

//---------------------------------------------------------
// strLineDesc_t:
//---------------------------------------------------------
struct strLineDesc_t
{
	const char	*line;
	int			length;
};

//---------------------------------------------------------
// nsStrLineSplit:
//---------------------------------------------------------
class nsStrLineSplit
{
public:
	nsStrLineSplit( const char *text );
	void					SetText( const char *text );
	int						GetLineCount() { return (int)m_list.size(); }
	const strLineDesc_t*	GetLine( int i );

private:
	typedef std::vector<strLineDesc_t>	lineList_t;

private:
	lineList_t	m_list;
};

#endif	//_StrLineSplit_H_