// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuEdit.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuEdit_H_
#define	_MenuEdit_H_

#include "MenuControl.h"
#include "BBox2.h"
#include "EditString.h"

class nsMenuEdit : nsMenuControl
{
public:
	static nsMenuControl*	Create() { return new nsMenuEdit; }

	const char*		GetText() { return m_text.GetLine(); }

protected:
	int				m_maxLen;
	bool			m_mouseOver;
	nsBBox2			m_box;
	nsEditString	m_text;
	nsVec2			m_textPos;

	bool			m_cursor;
	float			m_cursorTime;

protected:
	nsMenuEdit();

	virtual bool	Parse( script_state_t *ss );
	virtual bool	HitTest( float x, float y );
	virtual void	OnMouseIn();
	virtual void	OnMouseOut();
	virtual void	Move( float time );
	virtual void	Draw();
	virtual void	DrawDebug();

	virtual void	OnChar( char ch );
	virtual void	OnKeyDown( int key, bool rept );
};

#endif	//_MenuEdit_H_