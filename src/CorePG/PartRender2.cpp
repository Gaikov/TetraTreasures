// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartRender2.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "PartRender2.h"
#include "MathTools.h"
#include <pf/vertexset.h>

//---------------------------------------------------------
// nsPartRender2::nsPartRender2:
//---------------------------------------------------------
nsPartRender2::nsPartRender2( uint partReserve ) :
	nsRenPatchBuffer( partReserve ),
	m_partCount( 0 )
{

}

//---------------------------------------------------------
// nsPartRender2::DrawBegin:
//---------------------------------------------------------
void nsPartRender2::DrawBegin()
{
	m_partCount = 0;
}

//---------------------------------------------------------
// Vec3:
//---------------------------------------------------------
inline static void Vec3( TVec3 &v, nsVec2 &v2 )
{
	v.x = v2.x;
	v.y = v2.y;
	v.z = 0;
}

//---------------------------------------------------------
// nsPartRender2::AddParticle:
//---------------------------------------------------------
void nsPartRender2::AddParticle( const nsVec2 &pos, const nsVec2 &size, float angle, const nsColor &c )
{
	if ( m_partCount >= GetMaxPatches() )
		ReallocBuffers( GetMaxPatches() + 100 );

	TLitVert	*v = &m_vert[m_partCount * nsRenPatchBuffer::VERT_PER_PATCH];

	TColor32	color = c.ToColor32();
	for ( int i = 0; i < 4; ++i )
	{
		v[i].color = color;
		v[i].RESERVED = 0;
	}

	nsVec2	r, d;
	Math_RotateVectors( angle, r, d );

	r *= size.x * 0.5f;
	d *= size.y * 0.5f;

	Vec3( v[0].pos, pos - r - d );
	v[0].uv.x = 0;
	v[0].uv.y = 0;

	Vec3( v[1].pos, pos - r + d );
	v[1].uv.x = 0;
	v[1].uv.y = 1;

	Vec3( v[2].pos, pos + r + d );
	v[2].uv.x = 1;
	v[2].uv.y = 1;

	Vec3( v[3].pos, pos + r - d );
	v[3].uv.x = 1;
	v[3].uv.y = 0;

	m_partCount ++;
}

//---------------------------------------------------------
// nsPartRender2::DrawFlush:
//---------------------------------------------------------
void nsPartRender2::DrawFlush()
{
	if ( !m_partCount ) return;
	DrawBuffer( m_partCount );
	m_partCount = 0;
}
