// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuButtonSytle.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuButtonSytle.h"
#include "LocalMgr.h"

//---------------------------------------------------------
// nsMenuButtonStyle::nsMenuButtonStyle:
//---------------------------------------------------------
nsMenuButtonStyle::nsMenuButtonStyle() :
	m_font( 0 )
{

}

//---------------------------------------------------------
// nsMenuButtonStyle::Parse:
//---------------------------------------------------------
bool nsMenuButtonStyle::Parse( script_state_t *ss )
{
	if ( !nsMenuCtrlStyle::Parse( ss ) ) return false;
	m_font = g_local->GetFont( ps_get_str( ss, "font" ) );
	if ( !m_font ) return false;
	if ( !m_up.Parse( ss, "img_up" ) ) return false;

	m_over.Parse( ss, "img_over" );
	m_down.Parse( ss, "img_down" );

	ps_get_color( ss, "text_color", m_textColor );
	ps_get_2f( ss, "text_scale", m_textScale, nsVec2( 1, 1 ) );

	m_sndDown = TSound::Get( ps_get_str( ss, "sound_down", "" ) );
	m_sndOver = TSound::Get( ps_get_str( ss, "sound_over", "" ) );
	return true;
}

