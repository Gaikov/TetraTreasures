// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuCheck.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuCheck_H_
#define	_MenuCheck_H_

#include "MenuControl.h"
#include "BBox2.h"

class nsMenuCheck : public nsMenuControl
{
public:
	static nsMenuControl*	Create() { return new nsMenuCheck; }
	bool					IsChecked() { return m_checked; }

protected:
	str						m_text;
	nsVec2					m_textPos;
	nsBBox2					m_box;

	bool					m_checked;
	bool					m_mouseOver;
	bool					m_mouseDown;

protected:
	nsMenuCheck();
	
	virtual bool			Parse( script_state_t *ss );
	virtual bool			HitTest( float x, float y );
	virtual void			OnMouseIn();
	virtual void			OnMouseOut();
	virtual void			OnLButtonDown( float x, float y );
	virtual void			OnLButtonUp( float x, float y );
	virtual void			Move( float time ) {}
	virtual void			Draw();
	virtual void			DrawDebug();
};

#endif	//_MenuCheck_H_