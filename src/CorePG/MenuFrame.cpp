// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuFrame.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuFrame.h"
#include "Vec2.h"
#include "Color.h"

//---------------------------------------------------------
// nsMenuFrame::Parse:
//---------------------------------------------------------
bool nsMenuFrame::Parse( script_state_t *ss )
{
	nsVec2	pos, size;

	ps_get_2f( ss, "pos", pos );

	ps_get_2f( ss, "size", size );
	size.ToInt();
	if ( size.x < 3 ) size.x = 3;
	if ( size.y < 3 ) size.y = 3;

	float	cellX = 1, cellY = 1;
	m_tex = TTexture::Get( ps_get_str( ss, "texture", "" ) );
	if ( m_tex )
	{
		cellX = (float)m_tex->GetWidth() / 3.0f;
		cellY = (float)m_tex->GetHeight() / 3.0f;
	}

	for ( int x = 0; x < (int)size.x; ++x )
		for ( int y = 0; y < (int)size.y; ++y )
		{
			TLitVert	quad[4];

			quad[0].pos = TVec3( x * cellX, y * cellY, 0 );
			quad[0].uv.x = TexCoord( TexIdx( x, (int)size.x ) );
			quad[0].uv.y = TexCoord( TexIdx( y, (int)size.y ) );

			quad[1].pos = TVec3( x * cellX, (y+1) * cellY, 0 );
			quad[1].uv.x = TexCoord( TexIdx( x, (int)size.x ) );
			quad[1].uv.y = TexCoord( TexIdx( y+1, (int)size.y ) );

			quad[2].pos = TVec3( (x+1) * cellX, (y+1) * cellY, 0 );
			quad[2].uv.x = TexCoord( TexIdx( (x+1), (int)size.x ) );
			quad[2].uv.y = TexCoord( TexIdx( (y+1), (int)size.y ) );

			quad[3].pos = TVec3( (x+1) * cellX, y * cellY, 0 );
			quad[3].uv.x = TexCoord( TexIdx( (x+1), (int)size.x ) );
			quad[3].uv.y = TexCoord( TexIdx( y, (int)size.y ) );

			for ( int i = 0; i < 4; ++i )
				quad[i].pos += TVec3( pos.x, pos.y, 0 );

			AddQuad( quad );
		}

		return true;
}

//---------------------------------------------------------
// nsMenuFrame::Draw:
//---------------------------------------------------------
void nsMenuFrame::Draw()
{
	TRenderer *r = TRenderer::GetInstance();

	r->SetTexture( m_tex );
	TVertexSet	vs( &m_vert[0], m_vert.size() );
	r->DrawIndexedVertices( TRenderer::kDrawTriangles, vs, &m_idx[0], m_idx.size() );
}

//---------------------------------------------------------
// nsMenuFrame::AddQuad:
//---------------------------------------------------------
void nsMenuFrame::AddQuad( TLitVert v[4] )
{
	for ( int i = 0; i < 4; ++i )
	{
		v[i].color = nsColor::white.ToColor32();
		m_vert.push_back( v[i] );
	}
	
	uint16_t	size = (uint16_t)m_vert.size();
	m_idx.push_back( size - 4 );
	m_idx.push_back( size - 3 );
	m_idx.push_back( size - 2 );

	m_idx.push_back( size - 4 );
	m_idx.push_back( size - 2 );
	m_idx.push_back( size - 1 );
}

//---------------------------------------------------------
// nsMenuFrame::TexCoord: 0, 1, 2, 3
//---------------------------------------------------------
float nsMenuFrame::TexCoord( int idx )
{
	if ( !m_tex ) return 0;
	return idx / 3.0f;
}

//---------------------------------------------------------
// nsMenuFrame::TexIdx:
//---------------------------------------------------------
int nsMenuFrame::TexIdx( int cell, int size )
{
	if ( !cell )
		return 0;
	else if ( cell < size - 1 )
		return 1;
	else if ( cell < size )
		return 2;
	return 3;
}