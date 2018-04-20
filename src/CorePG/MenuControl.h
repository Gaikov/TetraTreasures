// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuControl.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuControl_H_
#define	_MenuControl_H_

#include "Parser.h"
#include "SmartPtr.h"
#include "MenuCtrlStyle.h"
#include "Vec2.h"
#include <pf/str.h>

class nsMenuWnd;

class nsMenuControl
{
friend class nsMenuMgr;
friend class nsMenuWnd;

public:
	typedef nsSmartPtr<nsMenuControl>	sp_t;

public:
	nsMenuControl();
	virtual ~nsMenuControl() {}

	virtual bool	Parse( script_state_t *ss );

	const char*			GetID() { return m_id.c_str(); }
	const char*			GetClassID() { return m_classID.c_str(); }
	nsMenuCtrlStyle*	GetStyle() { return m_style; }

	void			CaptureInc() { m_captured++; }
	void			CaptureDec() { m_captured--; }
	bool			IsCaptured() { return m_captured > 0; }

	virtual void	OnKeyUp( int key );
	virtual void	OnKeyDown( int key, bool rept );
	virtual void	OnChar( char ch );

	virtual void	OnLButtonUp( float x, float y );
	virtual void	OnLButtonDown( float x, float y );
	virtual void	OnMouseMove( float x, float y );

	virtual void	OnMouseIn() {}
	virtual void	OnMouseOut() {}

	virtual bool	HitTest( float x, float y ) { return false; }
	virtual void	Move( float time ) = 0;
	virtual void	Draw() = 0;
	virtual void	DrawDebug() = 0;

protected:
	nsVec2			m_pos;

protected:
	bool			SendOwnerEvent( const char *event );
	nsMenuWnd*		GetOwner() { return m_owner; }

private:
	nsMenuWnd		*m_owner;
	int				m_captured;
	str				m_id;
	str				m_classID;
	nsMenuCtrlStyle	*m_style;
};

#endif	//_MenuControl_H_