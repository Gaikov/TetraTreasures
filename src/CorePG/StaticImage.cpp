// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file StaticImage.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "StaticImage.h"

//---------------------------------------------------------
// nsStaticImage::Parse:
//---------------------------------------------------------
bool nsStaticImage::Parse( script_state_t *ss )
{
	if ( ps_block_begin( ss, "res" ) )
	{
		m_img.Parse( ss );
		ps_block_end( ss );
	}

	ps_get_2f( ss, "pos", m_pos );
	ps_get_2f( ss, "size", m_size, m_img.GetSize() );
	ps_get_color( ss, "color", m_color );
	return true;
}

//---------------------------------------------------------
// nsStaticImage::Draw:
//---------------------------------------------------------
void nsStaticImage::Draw()
{
	m_img.Draw( m_pos, m_size, 0, m_color );
}
