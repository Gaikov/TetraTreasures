// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuControl.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuControl.h"
#include "MenuMgr.h"
#include "log.h"
#include "StrTools.h"

//---------------------------------------------------------
// nsMenuControl::nsMenuControl:
//---------------------------------------------------------
nsMenuControl::nsMenuControl() :
	m_captured( 0 ),
	m_owner( 0 ),
	m_style( 0 ),
	m_classID( "base_ctrl" )
{

}

//---------------------------------------------------------
// nsMenuControl::Parse:
//---------------------------------------------------------
bool nsMenuControl::Parse( script_state_t *ss )
{
	m_id = ps_get_str( ss, "id", "noid" );
	const char *style = ps_get_str( ss, "style", "noid" );

	m_style = g_menu->StyleGet( m_classID.c_str(), style );
	if ( !m_style )
	{
		LogPrintf( PRN_ALL, "WARNING: menu style '%s' not found! (ctrl: %s)\n", style, m_id.c_str() );
		return false;
	}

	ps_get_2f( ss, "pos", m_pos );
	return true;
}

void nsMenuControl::OnKeyUp( int key )
{

}

void nsMenuControl::OnKeyDown( int key, bool rept )
{

}

void nsMenuControl::OnChar( char ch )
{

}

void nsMenuControl::OnLButtonUp( float x, float y )
{

}

void nsMenuControl::OnLButtonDown( float x, float y )
{

}

void nsMenuControl::OnMouseMove( float x, float y )
{

}

//---------------------------------------------------------
// nsMenuControl::SendOwnerEvent:
//---------------------------------------------------------
bool nsMenuControl::SendOwnerEvent( const char *msg )
{
	if ( !m_owner || !StrCheck( msg ) ) return false;
	return m_owner->OnCtrlEvent( this, msg );
}