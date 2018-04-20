// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file ImageView.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "ImageView.h"
#include "StrTools.h"

//---------------------------------------------------------
// nsImageView::nsImageView:
//---------------------------------------------------------
nsImageView::nsImageView( const char *fileName, const nsVec2 &texPos, const nsVec2 &texSize ) :
	m_texSize( texSize )
{
	if ( !StrCheck( fileName ) ) return;
	m_spr.tex = TTexture::Get( fileName );

	UpdateTexCoords( texPos, texSize );
}

//---------------------------------------------------------
// nsImageView::~nsImageView:
//---------------------------------------------------------
nsImageView::~nsImageView()
{
}

//---------------------------------------------------------
// nsImageView::Parse:
//---------------------------------------------------------
bool nsImageView::Parse( script_state_t *ss, const char *blockName )
{
	bool	res = false;
	if ( ps_block_begin( ss, blockName ) )
	{
		res = Parse( ss );
		ps_block_end( ss );
	}
	return res;
}

//---------------------------------------------------------
// nsImageView::Parse:
//---------------------------------------------------------
bool nsImageView::Parse( script_state_t *ss )
{
	m_spr.tex = TTexture::Get( ps_get_str( ss, "texture" ) );

	nsVec2	texPos;
	ps_get_2f( ss, "tex_pos", texPos );
	ps_get_2f( ss, "tex_size", m_texSize );
	
	UpdateTexCoords( texPos, m_texSize );
	return true;
}

//---------------------------------------------------------
// nsImageView::Draw:
//---------------------------------------------------------
void nsImageView::Draw( const nsVec2 &pos, const nsVec2 &size, float angle, const nsColor &c, uint align ) const
{
	m_spr.pos = pos;
	m_spr.size = size;
	m_spr.angle = angle;
	m_spr.center = Align_CalcSizeOffs( size, align );
	m_spr.center.ToInt();
	m_spr.color = c;
	RX_DrawSprite( m_spr );
}

//---------------------------------------------------------
// nsImageView::Draw:
//---------------------------------------------------------
void nsImageView::Draw( const nsVec2 &pos, const nsVec2 &size, const nsVec2 &center, float angle /*= 0*/, const nsColor &c /*= nsColor( 1, 1, 1, 1 )*/ ) const
{
	m_spr.pos = pos;
	m_spr.size = size;
	m_spr.angle = angle;
	m_spr.center = center;
	m_spr.center.ToInt();
	m_spr.color = c;
	RX_DrawSprite( m_spr );
}

//---------------------------------------------------------
// nsImageView::UpdateTexCoords:
//---------------------------------------------------------
void nsImageView::UpdateTexCoords( const nsVec2 &texPos, const nsVec2 &texSize )
{
	int	w = 1, h = 1;
	if ( m_spr.tex )
	{
		w = m_spr.tex->GetWidth();
		h = m_spr.tex->GetHeight();
	}
	float sizeX = texSize.x ? texSize.x : float(w) - texPos.x;
	float sizeY = texSize.y ? texSize.y : float(h) - texPos.y;

	m_spr.useTex = true;
	m_spr.tex1.x = texPos.x / float(w);
	m_spr.tex1.y = texPos.y / float(h);
	m_spr.tex2.x = sizeX / float(w) + m_spr.tex1.x;
	m_spr.tex2.y = sizeY / float(h) + m_spr.tex1.y;//*/
}


