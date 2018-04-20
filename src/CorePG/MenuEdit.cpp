// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuEdit.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuEdit.h"
#include "MenuEditStyle.h"
#include <pf/event.h>

//---------------------------------------------------------
// nsMenuEdit::nsMenuEdit:
//---------------------------------------------------------
nsMenuEdit::nsMenuEdit() :
	m_mouseOver( false ),
	m_text( 200 ),
	m_cursor( false ),
	m_cursorTime( 0 )
{

}

//---------------------------------------------------------
// nsMenuEdit::Parse:
//---------------------------------------------------------
bool nsMenuEdit::Parse( script_state_t *ss )
{
	if ( !nsMenuControl::Parse( ss ) ) return false;

	nsMenuEditStyle	*s = (nsMenuEditStyle*)GetStyle();
	nsVec2			size = s->m_up.GetSize();
	m_box.FromWH( size.x, size.y );

	m_textPos = m_pos;
	m_textPos.x += ps_get_f( ss, "text_margin" );
	m_textPos.y = m_pos.y + size.y * 0.5f;

	m_text.SetMaxLen( (int)ps_get_f( ss, "max_len", 100 ) );
	m_text.SetLine( ps_get_str( ss, "text", "" ) );
	
	return true;
}

//---------------------------------------------------------
// nsMenuEdit::HitTest:
//---------------------------------------------------------
bool nsMenuEdit::HitTest( float x, float y )
{
	return m_box.PointInBox( nsVec2( x, y ), m_pos );
}

//---------------------------------------------------------
// nsMenuEdit::OnMouseIn:
//---------------------------------------------------------
void nsMenuEdit::OnMouseIn()
{
	m_mouseOver = true;

	nsMenuEditStyle	*s = (nsMenuEditStyle*)GetStyle();
	if ( s && s->m_sndOver ) 
		s->m_sndOver->Play();
}

//---------------------------------------------------------
// nsMenuEdit::OnMouseOut:
//---------------------------------------------------------
void nsMenuEdit::OnMouseOut()
{
	m_mouseOver = false;
}

//---------------------------------------------------------
// nsMenuEdit::Move:
//---------------------------------------------------------
void nsMenuEdit::Move( float time )
{
	m_cursorTime -= time;
	if ( m_cursorTime <= 0 )
	{
		m_cursorTime += 0.2f;
		m_cursor = !m_cursor;
	}
}

//---------------------------------------------------------
// nsMenuEdit::Draw:
//---------------------------------------------------------
void nsMenuEdit::Draw()
{
	nsMenuEditStyle	*s = (nsMenuEditStyle*)GetStyle();

	if ( m_mouseOver )
		s->m_over.Draw( m_pos, s->m_over.GetSize() );
	else
		s->m_up.Draw( m_pos, s->m_up.GetSize() );

	Font_DrawAligned( s->m_font, m_text.GetLine(), m_textPos, 
		ALIGN_VERT_CENTER, s->m_textScale, s->m_textColor );

	if ( m_mouseOver && m_cursor )
	{
		nsVec2	pos = m_textPos;
		int		curPos = m_text.GetCursorPos();
		if ( curPos )
		{
			nsVec2	size;
			s->m_font->GetSize( m_text.GetLine(), size, curPos );
			size *= s->m_textScale;
			pos.x += size.x;
		}

		Font_DrawAligned( s->m_font, "_", pos, 
			ALIGN_VERT_CENTER, s->m_textScale, s->m_textColor );
	}
}

//---------------------------------------------------------
// nsMenuEdit::DrawDebug:
//---------------------------------------------------------
void nsMenuEdit::DrawDebug()
{

}

//---------------------------------------------------------
// nsMenuEdit::OnChar:
//---------------------------------------------------------
void nsMenuEdit::OnChar( char ch )
{
	if ( m_mouseOver && !iscntrl( (uchar)ch ) )
		m_text.TypeChar( ch );
}

//---------------------------------------------------------
// nsMenuEdit::OnKeyDown:
//---------------------------------------------------------
void nsMenuEdit::OnKeyDown( int key, bool rept )
{
	if ( !m_mouseOver ) return;

	if ( key == TEvent::kBackspace )
		m_text.KeyBackspace();
	else if ( key == TEvent::kDelete )
		m_text.KeyDelete();
	else if ( key == TEvent::kLeft )
		m_text.KeyLeft();
	else if ( key == TEvent::kRight )
		m_text.KeyRight();
}