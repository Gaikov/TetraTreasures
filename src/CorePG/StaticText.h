// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file StaticText.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_StaticText_H_
#define	_StaticText_H_

#include "SmartPtr.h"
#include "Font.h"
#include "Parser.h"
#include "StrLineSplit.h"
#include <pf/str.h>

class nsStaticText
{
public:
	typedef nsSmartPtr<nsStaticText>	sp_t;
public:
	nsStaticText();

	const char*	GetID() { return m_id.c_str(); }
	void		SetText( const char *text );
	bool		Parse( script_state_t *ss );
	void		Draw();
	
private:
	str				m_id;
	nsFont			*m_font;
	nsString		m_text;
	nsStrLineSplit	m_lines;
	nsVec2			m_pos;
	nsVec2			m_scale;
	nsColor			m_color;
	float			m_lineStep;
	uint			m_align;
};



#endif	//_StaticText_H_