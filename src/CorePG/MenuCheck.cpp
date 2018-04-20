// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuCheck.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuCheck.h"
#include "MenuCheckStyle.h"

//---------------------------------------------------------
// nsMenuCheck::nsMenuCheck:
//---------------------------------------------------------
nsMenuCheck::nsMenuCheck() :
	m_mouseOver( false ),
	m_mouseDown( false ),
	m_checked( false )
{

}

//---------------------------------------------------------
// nsMenuCheck::Parse:
//---------------------------------------------------------
bool nsMenuCheck::Parse( script_state_t *ss )
{
	if ( !nsMenuControl::Parse( ss ) ) return false;
	nsMenuCheckStyle	*s = (nsMenuCheckStyle*)GetStyle();

	m_text = ps_get_str( ss, "text", "nolabel" );
	float margin = ps_get_f( ss, "text_margin", 0 );
	nsVec2 size = s->m_up.GetSize();
	m_textPos = m_pos;
	m_textPos.x += size.x + margin;
	m_textPos.y += size.y * 0.5f;
	m_box.FromWH( size.x, size.y );

	return true;
}

//---------------------------------------------------------
// nsMenuCheck::HitTest:
//---------------------------------------------------------
bool nsMenuCheck::HitTest( float x, float y )
{
	return m_box.PointInBox( nsVec2( x, y ), m_pos );
}

//---------------------------------------------------------
// nsMenuCheck::OnMouseIn:
//---------------------------------------------------------
void nsMenuCheck::OnMouseIn()
{
	m_mouseOver = true;

	nsMenuCheckStyle	*s = (nsMenuCheckStyle*)GetStyle();
	if ( s && s->m_sndOver ) 
		s->m_sndOver->Play();
}

//---------------------------------------------------------
// nsMenuCheck::OnMouseOut:
//---------------------------------------------------------
void nsMenuCheck::OnMouseOut()
{
	m_mouseOver = false;
}

//---------------------------------------------------------
// nsMenuCheck::OnLButtonDown:
//---------------------------------------------------------
void nsMenuCheck::OnLButtonDown( float x, float y )
{
	m_mouseDown = true;
}

//---------------------------------------------------------
// nsMenuCheck::OnLButtonUp:
//---------------------------------------------------------
void nsMenuCheck::OnLButtonUp( float x, float y )
{
	m_mouseDown = false;
	if ( HitTest( x, y ) )
	{
		SendOwnerEvent( "check_click" );
		
		nsMenuCheckStyle	*s = (nsMenuCheckStyle*)GetStyle();
		m_checked = !m_checked;
		if ( s && s->m_sndDown )
			s->m_sndDown->Play();
	}
}

//---------------------------------------------------------
// nsMenuCheck::Draw:
//---------------------------------------------------------
void nsMenuCheck::Draw()
{
	nsMenuCheckStyle	*s = (nsMenuCheckStyle*)GetStyle();
	if ( m_mouseOver )
	{
		if ( m_mouseDown )
			s->m_down.Draw( m_pos, s->m_down.GetSize() );
		else
			s->m_over.Draw( m_pos, s->m_over.GetSize() );
	}
	else
		s->m_up.Draw( m_pos, s->m_up.GetSize() );

	if ( m_checked )
		s->m_check.Draw( m_pos, s->m_check.GetSize() );

	Font_DrawAligned( s->m_font, m_text.c_str(), m_textPos, 
		ALIGN_VERT_CENTER, s->m_textScale, s->m_textColor );
}

//---------------------------------------------------------
// nsMenuCheck::DrawDebug:
//---------------------------------------------------------
void nsMenuCheck::DrawDebug()
{

}