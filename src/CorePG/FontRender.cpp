// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FontRender.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "FontRender.h"
#include <pf/vertexset.h>

//---------------------------------------------------------
// nsFontRender::nsFontRender:
//---------------------------------------------------------
nsFontRender::nsFontRender( uint reserveChars ) :
	nsRenPatchBuffer( reserveChars )
{

}

//---------------------------------------------------------
// nsFontRender::DrawBegin:
//---------------------------------------------------------
void nsFontRender::DrawBegin( const nsVec2 &startPos )
{
	m_currPos = startPos;
	m_countChars = 0;
}

//---------------------------------------------------------
// nsFontRender::ResetPos:
//---------------------------------------------------------
void nsFontRender::ResetPos( const nsVec2 &pos )
{
	m_currPos = pos;
}

//---------------------------------------------------------
// nsFontRender::DrawFlush:
//---------------------------------------------------------
void nsFontRender::DrawFlush()
{
	if ( !m_countChars ) return;
	DrawBuffer( m_countChars );
	m_countChars = 0;
}

//---------------------------------------------------------
// nsFontRender::AddChar:
//---------------------------------------------------------
void nsFontRender::AddChar( const charView_t &cv, const nsVec2 &scale, TColor32 color )
{
	if ( m_countChars >= GetMaxPatches() )
		ReallocBuffers( GetMaxPatches() + 100 );

	TLitVert	*v = &m_vert[m_countChars * nsRenPatchBuffer::VERT_PER_PATCH];

	for ( int i = 0; i < 4; ++i ) v[i].color = color;

	nsVec2	p = m_currPos + nsVec2( cv.outOffs.x, -cv.outOffs.y ) * scale;
	nsVec2	s = cv.outSize * scale;

	v[0].pos = TVec3( p.x, p.y, 0 );
	v[0].uv.x = cv.texPos.x;
	v[0].uv.y = cv.texPos.y;

	v[1].pos = TVec3( p.x, p.y + s.y, 0 );
	v[1].uv.x = cv.texPos.x;
	v[1].uv.y = cv.texPos.y + cv.texSize.y;

	v[2].pos = TVec3( p.x + s.x, p.y + s.y, 0 );
	v[2].uv.x = cv.texPos.x + cv.texSize.x;
	v[2].uv.y = cv.texPos.y + cv.texSize.y;

	v[3].pos = TVec3( p.x + s.x, p.y, 0 );
	v[3].uv.x = cv.texPos.x + cv.texSize.x;
	v[3].uv.y = cv.texPos.y;

	m_currPos.x += cv.step * scale.x;
	m_countChars ++;
}

//---------------------------------------------------------
// nsFontRender::AddCharFX:
//---------------------------------------------------------
void nsFontRender::AddCharFX( const charView_t &cv, const nsVec2 &scale, const charDrawParams_t &dp )
{
	/*if ( m_countChars >= GetMaxPatches() )
		ReallocBuffers( GetMaxPatches() + 100 );

	vbVertex_t	*v = &m_vert[m_countChars * nsRenPatchBuffer::VERT_PER_PATCH];

	dword	color = dp.color.ToARGB();
	for ( int i = 0; i < 4; ++i ) v[i].c = color;

	nsVec2	p = m_currPos + cv.outOffs * scale;
	nsVec2	s = cv.outSize * scale;
	
	//модифицируем для эффекта
	s *= 0.5f;
	p.x += s.x;
	p.y -= s.y;
	s *= dp.scale;

	nsVec2	r, d;	//right, down
	Math_RotateVectors( dp.angle, r, d );
	d.Invert();

	r *= s.x;
	d *= s.y;

	v[0].v.FromVec2XY( p - r - d );
	v[0].tu = cv.texPos.x;
	v[0].tv = cv.texPos.y;

	v[1].v.FromVec2XY( p + d - r );
	v[1].tu = cv.texPos.x;
	v[1].tv = cv.texPos.y + cv.texSize.y;

	v[2].v.FromVec2XY( p + d + r );
	v[2].tu = cv.texPos.x + cv.texSize.x;
	v[2].tv = cv.texPos.y + cv.texSize.y;

	v[3].v.FromVec2XY( p + r - d );
	v[3].tu = cv.texPos.x + cv.texSize.x;
	v[3].tv = cv.texPos.y;

	m_currPos.x += cv.step * scale.x;
	m_countChars ++;//*/
}

//---------------------------------------------------------
// nsFontRender::AddStep:
//---------------------------------------------------------
void nsFontRender::AddStep( float step )
{
	m_currPos.x += step;
}
