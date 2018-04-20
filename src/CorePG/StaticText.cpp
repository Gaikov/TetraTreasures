// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file StaticText.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "StaticText.h"
#include "StrTools.h"
#include "LocalMgr.h"
#include "Align.h"

//---------------------------------------------------------
// nsStaticText::nsStaticText:
//---------------------------------------------------------
nsStaticText::nsStaticText() :
	m_font( 0 ),
	m_lines( 0 )
{

}

//---------------------------------------------------------
// nsStaticText::SetText:
//---------------------------------------------------------
void nsStaticText::SetText( const char *text )
{
	m_text = text;
	if ( m_lineStep ) m_lines.SetText( m_text );
}

//---------------------------------------------------------
// nsStaticText::Parse:
//---------------------------------------------------------
bool nsStaticText::Parse( script_state_t *ss )
{
	m_id = ps_get_str( ss, "id", "noid" );
	m_font = g_local->GetFont( ps_get_str( ss, "font" ) );
	if ( !m_font ) return false;
	m_text = ps_get_str( ss, "text", "" );
	m_lines.SetText( m_text );

		ps_get_2f( ss, "scale", m_scale, nsVec2( 1, 1 ) );
	ps_get_color( ss, "color", m_color );
	m_align = Align_ParseHorz( ss );
	m_align |= Align_ParseVert( ss );
	ps_get_2f( ss, "pos", m_pos );
	m_lineStep = ps_get_f( ss, "line_step" );

	return true;
}

//---------------------------------------------------------
// nsStaticText::Draw:
//---------------------------------------------------------
void nsStaticText::Draw()
{
	if ( m_lineStep )
	{
		const strLineDesc_t	*line;
		nsVec2				pos = m_pos;
		for ( int i = 0; line = m_lines.GetLine( i ); ++i )
		{
			Font_DrawAligned( m_font, line->line, pos, m_align, m_scale, m_color, line->length );
			pos.y += m_lineStep;
		}
	}
	else
		Font_DrawAligned( m_font, m_text, m_pos, m_align, m_scale, m_color );
}
