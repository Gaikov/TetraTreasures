// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuButton.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuButton_H_
#define	_MenuButton_H_

#include "MenuControl.h"
#include "BBox2.h"

class nsMenuButton : public nsMenuControl
{
public:
	static nsMenuControl*	Create() { return new nsMenuButton; }

private:
	str		m_text;
	nsVec2	m_textPos;
	nsBBox2	m_box;
	bool	m_over;
	bool	m_mouseDown;
	bool	m_close;

private:
	nsMenuButton();

	virtual bool			Parse( script_state_t *ss );
	virtual bool			HitTest( float x, float y );
	virtual void			OnMouseIn();
	virtual void			OnMouseOut();
	virtual void			OnLButtonDown( float x, float y );
	virtual void			OnLButtonUp( float x, float y );
	virtual void			Move( float time );
	virtual	void			Draw();
	virtual void			DrawDebug();
};

#endif	//_MenuButton_H_