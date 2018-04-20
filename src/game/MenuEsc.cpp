// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuEsc.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuEsc.h"
#include <pf/event.h>

nsMenuEsc::nsMenuEsc( const char *id ) :
	nsMenuWnd( id )
{

}

//---------------------------------------------------------
// nsMenuEsc::OnKeyDown:
//---------------------------------------------------------
void nsMenuEsc::OnKeyDown( int key, bool rept )
{
	if ( key == TEvent::kEscape )
		Close();
	else
		nsMenuWnd::OnKeyDown( key, rept );
}

//---------------------------------------------------------
// nsMenuEsc::OnCtrlEvent:
//---------------------------------------------------------
bool nsMenuEsc::OnCtrlEvent( nsMenuControl *ctrl, const char *msg )
{
	nsString	id = ctrl->GetID();
	if ( StrEqual( msg, "button_click" ) )
	{
		if ( id == "ID_RESUME" )
		{
			Close();
			return true;
		}
		else if ( id == "ID_MORE_GAMES" )
		{
			TPlatform::GetInstance()->OpenBrowser( "http://free-casual-game.com" );
			return true;
		}
		else if ( id == "ID_MAIN" )
		{
			Close();
			g_menu->WndActivate( "IDM_MAIN" );
			return true;
		}
		else if ( id == "ID_NEW_GAME" )
		{
			if ( m_parent )
				m_parent->OnChildEvent( this, "CLICK_NEW_GAME" );
			Close();
			g_menu->WndActivate( "IDM_ADS" );
			return true;
		}

	}
	return false;
}