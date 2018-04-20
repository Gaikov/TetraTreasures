// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuMgr.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuMgr_H_
#define	_MenuMgr_H_

#include "headers.h"
#include "MenuWnd.h"
#include "MenuControl.h"
#include "MenuCtrlStyle.h"

class nsMenuMgr
{
public:
	typedef nsMenuControl*		(*createCtrlFunc_t)();
	typedef nsMenuCtrlStyle*	(*createStyleFunc_t)();

public:
	static bool			Init();
	static void			Release();

	bool				IsActive();
	nsMenuWnd*			WndGetActive();
	nsMenuWnd*			WndActivate( const char *id );
	void				WndCloseTop();
	bool				WndRegister( nsMenuWnd *wnd, const char *fileName );

	bool				CtrlRegister( const char *ctrlClass, createCtrlFunc_t ctrlFunc, createStyleFunc_t styleFunc );
	nsMenuControl*		CtrlCreate( const char *ctrlClass );
	
	bool				StylesLoad( const char *fileName );
	nsMenuCtrlStyle*	StyleCreate( const char *ctrlClass );
	nsMenuCtrlStyle*	StyleGet( const char *ctrlClass, const char *styleID );

	void				Loop( float time );
	void				Draw();

protected:
	void				StackPush( nsMenuWnd *wnd );
	nsMenuWnd*			StackPop();
	nsMenuWnd*			StackTop();

private:
	typedef struct ctrlDesc_t
	{
		str					classID;
		createCtrlFunc_t	createCtrl;
		createStyleFunc_t	createStyle;
	};

	typedef std::vector<ctrlDesc_t>				ctrlDescList_t;
	typedef std::vector<nsMenuWnd::sp_t>		wndList_t;
	typedef std::vector<nsMenuCtrlStyle::sp_t>	styleList_t;
	typedef std::vector<nsMenuWnd*>				stackList_t;
	typedef std::vector<nsMenuWnd*>				drawList_t;
	
private:
	bool				m_valid;

	wndList_t			m_wndList;
	
	stackList_t			m_wndStack;

	drawList_t			m_drawList;

	ctrlDescList_t		m_ctrlDescList;
	styleList_t			m_styleList;

private:
	nsMenuMgr();
	~nsMenuMgr();
};

extern nsMenuMgr *g_menu;

#endif	//_MenuMgr_H_