// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuMsg.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuMsg.h"

nsMenuMsg::nsMenuMsg( const char *id ) :
	nsMenuWnd( id )
{

}

//---------------------------------------------------------
// nsMenuMsg::ShowMsg:
//---------------------------------------------------------
void nsMenuMsg::ShowMsg( const char *caption, const char *msg )
{
	nsMenuMsg	*wnd = (nsMenuMsg*)g_menu->WndActivate( "IDM_MESSAGE" );
	if ( wnd )
	{
		wnd->SetCaption( caption );
		wnd->SetMessage( msg );
	}
}

//---------------------------------------------------------
// nsMenuMsg::SetCaption:
//---------------------------------------------------------
void nsMenuMsg::SetCaption( const char *caption )
{
	nsStaticText	*text = GetStaticByID( "IDT_CAPTION" );
	if ( text )	text->SetText( caption );
}

//---------------------------------------------------------
// nsMenuMsg::SetMessage:
//---------------------------------------------------------
void nsMenuMsg::SetMessage( const char *msg )
{
	nsStaticText	*text = GetStaticByID( "IDT_MESSAGE" );
	if ( text )	text->SetText( msg );
}

//---------------------------------------------------------
// nsMenuMsg::OnCtrlEvent:
//---------------------------------------------------------
bool nsMenuMsg::OnCtrlEvent( nsMenuControl *ctrl, const char *msg )
{
	if ( StrEqual( msg, "button_click" ) )
	{
		if ( StrEqual( ctrl->GetID(), "ID_OK" ) )
		{
			Close();
			return true;
		}
	}

	return false;
}