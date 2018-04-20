// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartDesc.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_PartDesc_H_
#define	_PartDesc_H_

#include "Parser.h"
#include "Vec2.h"
#include "Color.h"
#include "MathTools.h"
#include <pf/texture.h>

class nsPartDesc
{
friend class nsPartState;

public:
	bool			Parse( const char *fileName );
	bool			Parse( script_state_t *ss );
	
	TTextureRef		GetTexture();
	inline float	CalcSizeScale() { return Math_RandRange( m_sizeScale.x, m_sizeScale.y ); }
	float			CalcSize( float lerp );
	inline float	CalcGravity() { return Math_RandRange( m_grav.x, m_grav.y ); }
	inline float	CalcAngle() { return Math_RandRange( m_angle1, m_angle2 ); }
	inline float	CalcRotVel() { return Math_RandRange( m_angleRot.x, m_angleRot.y ); }
	inline void		CalcPos( nsVec2 &pos );
	inline void		CalcVel( nsVec2 &vel );
	inline float	CalcLifeVel();
	void			CalcColor( float lerp, nsColor &color );

private:
	struct colorKey_t
	{
		float	key;
		nsColor	c;
	};

	typedef std::vector<nsVec2>		vecList_t;
	typedef std::vector<colorKey_t>	colorList_t;
	
private:
	TTextureRef				m_tex;
	TRenderer::EBlendMode	m_blend;
	int						m_count;
	nsVec2					m_grav;
	nsVec2					m_sizeScale;
	vecList_t				m_size;
	float					m_angle1, m_angle2;
	nsVec2					m_angleRot;
	nsVec2					m_pos1, m_pos2;
	nsVec2					m_vel1, m_vel2;
	float					m_velNorm;
	float					m_lifeTime1, m_lifeTime2;
	colorList_t				m_color;
};

//---------------------------------------------------------
// nsPartDesc::CalcPos:
//---------------------------------------------------------
void nsPartDesc::CalcPos( nsVec2 &pos )
{
	pos.x = Math_RandRange( m_pos1.x, m_pos2.x );
	pos.y = Math_RandRange( m_pos1.y, m_pos2.y );
}

//---------------------------------------------------------
// nsPartDesc::CalcVel:
//---------------------------------------------------------
void nsPartDesc::CalcVel( nsVec2 &vel )
{
	vel.x = Math_RandRange( m_vel1.x, m_vel2.x );
	vel.y = Math_RandRange( m_vel1.y, m_vel2.y );
	if ( m_velNorm )
	{
		vel.Norm();
		vel *= m_velNorm;
	}
}

//---------------------------------------------------------
// nsPartDesc::CalcLifeVel:
//---------------------------------------------------------
float nsPartDesc::CalcLifeVel()
{
	float	time = Math_RandRange( m_lifeTime1, m_lifeTime2 );
	return 1.0f / time;
}

#endif	//_PartDesc_H_