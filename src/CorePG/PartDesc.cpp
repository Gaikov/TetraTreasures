// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartDesc.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "PartDesc.h"
#include "ParseFile.h"
#include "log.h"
#include "StrTools.h"
#include "Str.h"

//---------------------------------------------------------
// nsPartDesc::Parse:
//---------------------------------------------------------
bool nsPartDesc::Parse( const char *fileName )
{
	if ( !StrCheck( fileName ) ) return false;

	nsParseFile		pf;
	script_state_t *ss = pf.BeginFile( fileName );
	if ( !ss )
	{
		LogPrintf( PRN_ALL, "WARNING: can't parse particle desc: '%s'\n", fileName );
		return false;
	}

	return Parse( ss );
}

//---------------------------------------------------------
// nsPartDesc::Parse:
//---------------------------------------------------------
bool nsPartDesc::Parse( script_state_t *ss )
{
	m_tex = TTexture::Get( ps_get_str( ss, "texture", "" ) );
	
	nsString	blend = ps_get_str( ss, "blend_mode", "blend" );
	if ( blend == "add" )
		m_blend = TRenderer::kBlendAdditiveAlpha;
	else if ( blend == "mul" )
		m_blend = TRenderer::kBlendMultiplicative;
	else if ( blend == "sub" )
		m_blend = TRenderer::kBlendSubtractive;
	else
		m_blend = TRenderer::kBlendNormal;
	
	m_count = (int)fabsf( ps_get_f( ss, "part_count", 10 ) );

	ps_get_2f( ss, "size_scale", m_sizeScale, nsVec2( 1, 1 ) );

	m_size.clear();
	if ( ps_var_begin( ss, "size_key" ) )
	{
		do 
		{
			nsVec2	s;
			if ( ps_var_2f( ss, s ) )
			{
				Math_Clamp( s.x, 0, 1 );
				m_size.push_back( s );
			}
		}
		while( ps_var_next( ss ) );
	}

	ps_get_2f( ss, "gravity", m_grav, nsVec2( 0, 0 ) );

	m_angle1 = ps_get_f( ss, "angle1" );
	m_angle2 = ps_get_f( ss, "angle2" );
	ps_get_2f( ss, "angle_rot", m_angleRot, nsVec2( 0, 0 ) );

	ps_get_2f( ss, "pos1", m_pos1 );
	ps_get_2f( ss, "pos2", m_pos2 );

	ps_get_2f( ss, "vel1", m_vel1 );
	ps_get_2f( ss, "vel2", m_vel2 );
	m_velNorm = ps_get_f( ss, "vel_norm" );

	m_lifeTime1 = fabsf( ps_get_f( ss, "life_time1" ) );
	m_lifeTime2 = fabsf( ps_get_f( ss, "life_time2" ) );

	m_color.clear();
	if ( ps_block_begin( ss, "color_key" ) )
	{
		do
		{
			colorKey_t	c;
			c.key = ps_get_f( ss, "key" );
			Math_Clamp( c.key, 0, 1 );

			ps_get_color( ss, "color", c.c );
			m_color.push_back( c );
		}
		while ( ps_block_next( ss ) );
		ps_block_end( ss );
	}

	return true;
}

//---------------------------------------------------------
// nsPartDesc::CalcSize:
//---------------------------------------------------------
float nsPartDesc::CalcSize( float lerp )
{
	size_t	count = m_size.size();
	if ( !count ) return 0;

	nsVec2	*s = &m_size[0];
	for ( ; count; count--, s++ )
	{
		if ( count == 1 )
			return s->y;
		else
		{
			nsVec2	*s2 = s + 1;
			if ( lerp > s->x && lerp <= s2->x )
			{
				float len = s2->x - s->x;
				float t = (lerp - s->x) / len;
				return Math_Lerp( s->y, s2->y, t );
			}
		}
	}

	return 0;
}

//---------------------------------------------------------
// nsPartDesc::CalcColor:
//---------------------------------------------------------
void nsPartDesc::CalcColor( float lerp, nsColor &color )
{
	size_t	count = m_color.size();
	if ( !count )
	{
		color = nsColor::white;
		return;
	}

	colorKey_t	*c = &m_color[0];
	for ( ; count; count--, c++ )
	{
		if ( count == 1 )
		{
			color = c->c;
			return;
		}
		else
		{
			colorKey_t	*c2 = c + 1;
			if ( lerp > c->key && lerp <= c2->key )
			{
				float len = c2->key - c->key;
				float t = (lerp - c->key) / len;
				color.FromLerp( c->c, c2->c, t );
				return;
			}
		}
	}
}