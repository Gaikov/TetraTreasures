// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuWnd.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuWnd_H_
#define	_MenuWnd_H_

#include <pf/str.h>
#include "UserInput.h"
#include "SmartPtr.h"
#include "Parser.h"
#include "StaticImage.h"
#include "MenuControl.h"
#include "StaticText.h"
#include "MenuFrame.h"

class nsMenuWnd : public IUserInput
{
friend class nsMenuMgr;

public:
	typedef	nsSmartPtr<nsMenuWnd>	sp_t;

public:
	nsMenuWnd( const char *menuID );
	virtual ~nsMenuWnd();

	const char*		GetID() { return m_id.c_str(); }

	nsStaticText*	GetStaticByID( const char *id );
	nsMenuControl*	GetCtrlByID( const char *id, const char *classID = 0 );

	virtual bool	Parse( script_state_t *ss );
	virtual void	Loop( float time );
	virtual void	Draw();

	virtual bool	OnEvent( const char *msg );
	virtual bool	OnCtrlEvent( nsMenuControl *ctrl, const char *msg );
	virtual bool	OnChildEvent( nsMenuWnd *wnd, const char *msg );

	void			Close();

protected:
	nsMenuWnd		*m_parent;
	bool			m_drawParent;

protected:
	virtual void	OnKeyUp( int key );
	virtual void	OnKeyDown( int key, bool rept );
	virtual void	OnChar( char ch );

	virtual void	OnLButtonUp( float x, float y );
	virtual void	OnLButtonDown( float x, float y );
	virtual void	OnRButtonUp( float x, float y ) {}
	virtual void	OnRButtonDown( float x, float y ) {}
	virtual void	OnMouseMove( float x, float y );

private:
	typedef std::vector<nsStaticText::sp_t>		textList_t;
	typedef std::vector<nsStaticImage::sp_t>	imgList_t;
	typedef std::vector<nsMenuControl::sp_t>	ctrlList_t;
	typedef std::vector<nsMenuFrame::sp_t>		frameList_t;
	
private:
	str				m_id;

	textList_t		m_textList;
	imgList_t		m_imgList;
	ctrlList_t		m_ctrlList;
	frameList_t		m_frameList;

	nsMenuControl	*m_focusCtrl;
	nsMenuControl	*m_captureCtrl;
};

#endif	//_MenuWnd_H_