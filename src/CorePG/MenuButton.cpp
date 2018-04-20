// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuButton.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuButton.h"
#include "MenuButtonSytle.h"
#include "MenuWnd.h"

//---------------------------------------------------------
// nsMenuButton::nsMenuButton:
//---------------------------------------------------------
nsMenuButton::nsMenuButton() :
	m_over( false ),
	m_mouseDown( false )
{

}

//---------------------------------------------------------
// nsMenuButton::Parse:
//---------------------------------------------------------
bool nsMenuButton::Parse( script_state_t *ss )
{
	if ( !nsMenuControl::Parse( ss ) ) return false;
	nsMenuButtonStyle	*s = (nsMenuButtonStyle*)GetStyle();

	m_textPos = m_pos;
	nsVec2	size = s->m_up.GetSize();
	m_textPos += size * 0.5f;

	m_box.FromWH( size.x, size.y );
	
	m_text = ps_get_str( ss, "text", "noname" );
	m_close = ps_get_f( ss, "close" ) ? true : false;

	return true;
}

//---------------------------------------------------------
// nsMenuButton::HitTest:
//---------------------------------------------------------
bool nsMenuButton::HitTest( float x, float y )
{
	return m_box.PointInBox( nsVec2( x, y ), m_pos );
}

//---------------------------------------------------------
// nsMenuButton::OnMouseIn:
//---------------------------------------------------------
void nsMenuButton::OnMouseIn()
{
	m_over = true;

	nsMenuButtonStyle	*s = (nsMenuButtonStyle*)GetStyle();
	if ( s && s->m_sndOver ) 
		s->m_sndOver->Play();
}

//---------------------------------------------------------
// nsMenuButton::OnMouseOut:
//---------------------------------------------------------
void nsMenuButton::OnMouseOut()
{
	m_over = false;
}

//---------------------------------------------------------
// nsMenuButton::OnLButtonDown:
//---------------------------------------------------------
void nsMenuButton::OnLButtonDown( float x, float y )
{
	m_mouseDown = true;
}

//---------------------------------------------------------
// nsMenuButton::OnLButtonUp:
//---------------------------------------------------------
void nsMenuButton::OnLButtonUp( float x, float y )
{
	m_mouseDown = false;
	if ( HitTest( x, y ) )
	{
		SendOwnerEvent( "button_click" );
		if ( m_close && GetOwner() ) GetOwner()->Close();

		nsMenuButtonStyle	*s = (nsMenuButtonStyle*)GetStyle();
		if ( s && s->m_sndDown )
			s->m_sndDown->Play();
	}
}

//---------------------------------------------------------
// nsMenuButton::Move:
//---------------------------------------------------------
void nsMenuButton::Move( float time )
{

}

//---------------------------------------------------------
// nsMenuButton::Draw:
//---------------------------------------------------------
void nsMenuButton::Draw()
{
	nsMenuButtonStyle	*s = (nsMenuButtonStyle*)GetStyle();
	if ( m_over )
	{
		if ( m_mouseDown )
			s->m_down.Draw( m_pos, s->m_down.GetSize() );
		else
			s->m_over.Draw( m_pos, s->m_over.GetSize() );
	}
	else
		s->m_up.Draw( m_pos, s->m_up.GetSize() );

	Font_DrawAligned( s->m_font, m_text.c_str(), m_textPos, 
		ALIGN_HORZ_CENTER | ALIGN_VERT_CENTER, s->m_textScale,
		s->m_textColor );
}

//---------------------------------------------------------
// nsMenuButton::DrawDebug:
//---------------------------------------------------------
void nsMenuButton::DrawDebug()
{
	RX_DrawCross( m_pos, 20 );
	RX_DrawCross( m_textPos, 20, nsColor::red );
	RX_DrawBBox( m_pos, m_box, nsColor::yellow );
}