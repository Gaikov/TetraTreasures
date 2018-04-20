// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuMgr.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuMgr.h"
#include "StrTools.h"
#include "ParseFile.h"
#include "log.h"

#include "MenuButton.h"
#include "MenuButtonSytle.h"
#include "MenuCheck.h"
#include "MenuCheckStyle.h"
#include "MenuEdit.h"
#include "MenuEditStyle.h"

nsMenuMgr *g_menu = 0;

//---------------------------------------------------------
// nsMenuMgr::nsMenuMgr:
//---------------------------------------------------------
nsMenuMgr::nsMenuMgr() :
	m_valid( true )
{
	CtrlRegister( "simple_button", nsMenuButton::Create, nsMenuButtonStyle::Create );
	CtrlRegister( "simple_check", nsMenuCheck::Create, nsMenuCheckStyle::Create );
	CtrlRegister( "simple_edit", nsMenuEdit::Create, nsMenuEditStyle::Create );
}

//---------------------------------------------------------
// nsMenuMgr::~nsMenuMgr:
//---------------------------------------------------------
nsMenuMgr::~nsMenuMgr()
{

}

//---------------------------------------------------------
// nsMenuMgr::Init:
//---------------------------------------------------------
bool nsMenuMgr::Init()
{
	if ( !g_menu )
	{
		g_menu = new nsMenuMgr;
		if ( !g_menu->m_valid )
		{
			delete g_menu;
			g_menu = 0;
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------
// nsMenuMgr::Release:
//---------------------------------------------------------
void nsMenuMgr::Release()
{
	if ( g_menu )
	{
		delete g_menu;
		g_menu = 0;
	}
}

//---------------------------------------------------------
// nsMenuMgr::IsActive:
//---------------------------------------------------------
bool nsMenuMgr::IsActive()
{
	return !m_wndStack.empty();
}

//---------------------------------------------------------
// nsMenuMgr::WndGetActive:
//---------------------------------------------------------
nsMenuWnd* nsMenuMgr::WndGetActive()
{
	return StackTop();
}

//---------------------------------------------------------
// nsMenuMgr::WndActivate:
//---------------------------------------------------------
nsMenuWnd* nsMenuMgr::WndActivate( const char *id )
{
	if ( !StrCheck( id ) ) return 0;

	wndList_t::iterator	it;
	for ( it = m_wndList.begin(); it != m_wndList.end(); ++it )
	{
		nsMenuWnd	*wnd = (*it);
		if ( StrEqual( wnd->GetID(), id ) )
		{
			nsMenuWnd	*top = StackTop();
			StackPush( wnd );
			
			if ( top ) top->OnEvent( "deactivate" );
			wnd->m_parent = top;
			wnd->OnEvent( "open" );
			wnd->OnEvent( "activate" );
			return wnd;
		}
	}
	return 0;
}

//---------------------------------------------------------
// nsMenuMgr::WndCloseTop:
//---------------------------------------------------------
void nsMenuMgr::WndCloseTop()
{
	if ( !m_wndStack.size() ) return;

	nsMenuWnd	*wnd = StackPop();
	nsMenuWnd	*top = StackTop();
	
	wnd->OnEvent( "deactivate" );
	wnd->OnEvent( "close" );
	wnd->m_parent = 0;
	if ( top ) top->OnEvent( "activate" );
}

//---------------------------------------------------------
// nsMenuMgr::WndRegister:
//---------------------------------------------------------
bool nsMenuMgr::WndRegister( nsMenuWnd *wnd, const char *fileName )
{
	if ( !wnd ) return false;

	if ( StrCheck( fileName ) )
	{
		nsParseFile	pf;
		script_state_t	*ss = pf.BeginFile( fileName );
		if ( !ss || !wnd->Parse( ss ) )
		{
			LogPrintf( PRN_ALL, "WARNING: can't parse menu '%s'\n", fileName );
			delete wnd;
			return false;
		}
	}

	m_wndList.push_back( wnd );
	return true;
}

//---------------------------------------------------------
// nsMenuMgr::CtrlRegister:
//---------------------------------------------------------
bool nsMenuMgr::CtrlRegister( const char *ctrlClass, createCtrlFunc_t ctrlFunc, createStyleFunc_t styleFunc )
{
	ctrlDesc_t	desc;
	desc.classID = ctrlClass;
	desc.createCtrl = ctrlFunc;
	desc.createStyle = styleFunc;

	m_ctrlDescList.push_back( desc );
	return true;
}

//---------------------------------------------------------
// nsMenuMgr::CtrlCreate:
//---------------------------------------------------------
nsMenuControl* nsMenuMgr::CtrlCreate( const char *ctrlClass )
{
	if ( !StrCheck( ctrlClass ) ) return 0;

	ctrlDescList_t::iterator	it;
	for ( it = m_ctrlDescList.begin(); it != m_ctrlDescList.end(); ++it )
	{
		ctrlDesc_t	&desc = (*it);
		if ( desc.classID == ctrlClass )
		{
			nsMenuControl	*ctrl = desc.createCtrl();
			ctrl->m_classID = desc.classID;
			return ctrl;
		}
	}

	return 0;
}

//---------------------------------------------------------
// nsMenuMgr::StylesLoad:
//---------------------------------------------------------
bool nsMenuMgr::StylesLoad( const char *fileName )
{
	LogPrintf( PRN_ALL, "...Parsing menu styles: '%s'\n", fileName );
	
	nsParseFile	pf;
	script_state_t *ss = pf.BeginFile( fileName );
	if ( !ss )
	{
		LogPrintf( PRN_ALL, "WARNING: can't register styles '%s'\n", fileName );
		return false;
	}

	size_t	prevCount = m_styleList.size();
	if ( ps_block_begin( ss, 0 ) )
	{
		do 
		{
			char	name[256];
			ps_block_get( ss, name, 256 );

			nsMenuCtrlStyle	*style = StyleCreate( name );
			if ( style && style->Parse( ss ) )
				m_styleList.push_back( style );
		}
		while( ps_block_next( ss ) );

		ps_block_end( ss );
	}

	LogPrintf( PRN_ALL, "%i - styles loaded\n", m_styleList.size() - prevCount );
	return true;
}

//---------------------------------------------------------
// nsMenuMgr::StyleCreate:
//---------------------------------------------------------
nsMenuCtrlStyle* nsMenuMgr::StyleCreate( const char *ctrlClass )
{
	if ( !StrCheck( ctrlClass ) ) return 0;

	ctrlDescList_t::iterator	it;
	for ( it = m_ctrlDescList.begin(); it != m_ctrlDescList.end(); ++it )
	{
		ctrlDesc_t	&desc = (*it);
		if ( desc.classID == ctrlClass )
		{
			nsMenuCtrlStyle	*style = desc.createStyle();
			style->m_classID = ctrlClass;
			return style;
		}
	}

	return 0;
}

//---------------------------------------------------------
// nsMenuMgr::StyleGet:
//---------------------------------------------------------
nsMenuCtrlStyle* nsMenuMgr::StyleGet( const char *ctrlClass, const char *styleID )
{
	if ( !StrCheck( ctrlClass ) || !StrCheck( styleID )	) return 0;

	styleList_t::iterator	it;
	for ( it = m_styleList.begin(); it != m_styleList.end(); ++it )
	{
		nsMenuCtrlStyle::sp_t	&s = (*it);
		if ( StrEqual( s->GetClassID(), ctrlClass )
			&& StrEqual( s->GetID(), styleID ) )
			return s;
	}
	return 0;
}

//---------------------------------------------------------
// nsMenuMgr::Loop:
//---------------------------------------------------------
void nsMenuMgr::Loop( float time )
{
	nsMenuWnd	*wnd = StackTop();
	if ( wnd ) wnd->Loop( time );
}

//---------------------------------------------------------
// nsMenuMgr::Draw:
//---------------------------------------------------------
void nsMenuMgr::Draw()
{
	m_drawList.clear();

	nsMenuWnd	*prev = 0;
	for ( int i = m_wndStack.size() - 1; i >= 0; --i )
	{
		nsMenuWnd	*wnd = m_wndStack[i];
		if ( !prev )
			m_drawList.push_back( wnd );
		else if ( prev->m_drawParent )
			m_drawList.push_back( wnd );
		else
			break;

		prev = wnd;
	}

	for ( int i = m_drawList.size() - 1; i >= 0; --i )
	{
		nsMenuWnd	*wnd = m_drawList[i];
		wnd->Draw();
	}
}

//---------------------------------------------------------
// nsMenuMgr::StackPush:
//---------------------------------------------------------
void nsMenuMgr::StackPush( nsMenuWnd *wnd )
{
	m_wndStack.push_back( wnd );
}

//---------------------------------------------------------
// nsMenuMgr::StackPop:
//---------------------------------------------------------
nsMenuWnd* nsMenuMgr::StackPop()
{
	size_t	size = m_wndStack.size();
	if ( !size ) return 0;

	nsMenuWnd	*top = m_wndStack[size - 1];
	m_wndStack.resize( size - 1 );
	return top;
}

//---------------------------------------------------------
// nsMenuMgr::StackTop:
//---------------------------------------------------------
nsMenuWnd* nsMenuMgr::StackTop()
{
	size_t	size = m_wndStack.size();
	if ( !size ) return 0;
	
	return m_wndStack[size - 1];
}