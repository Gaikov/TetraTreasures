// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartState.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "PartState.h"
#include "PartManager.h"

//---------------------------------------------------------
// nsPartState::nsPartState:
//---------------------------------------------------------
nsPartState::nsPartState() :
	m_desc( 0 )
{

}

//---------------------------------------------------------
// nsPartState::MakeBlast:
//---------------------------------------------------------
void nsPartState::MakeBlast()
{
	for ( int i = 0; i < m_desc->m_count; ++i )
		EmitPart();
}

//---------------------------------------------------------
// nsPartState::DrawParticles:
//---------------------------------------------------------
void nsPartState::DrawParticles()
{
	nsPartManager::partCtrl_t	&ctrl = g_partManager->m_partCtrl;
	if ( !ctrl.FetchBegin( this ) ) return;

	TRenderer		*r = TRenderer::GetInstance();
	nsPartRender2	&ren = g_partManager->m_ren;
	r->SetTexture( m_desc->m_tex );

	ren.DrawBegin();
	particle_t		*p;
	while ( p = ctrl.Fetch() )
	{
		nsColor	c;
		m_desc->CalcColor( 1 - p->life, c );
		float	size = m_desc->CalcSize( 1 - p->life ) * p->scale;
		nsVec2	pos = p->pos;
		if ( m_relPos ) pos += m_pos;
		ren.AddParticle( pos, nsVec2( size, size ), p->angle, c );
	}

	r->SetBlendMode( m_desc->m_blend );
	ren.DrawFlush();
	r->SetBlendMode( TRenderer::kBlendNormal );
}

//---------------------------------------------------------
// nsPartState::Init:
//---------------------------------------------------------
void nsPartState::Init( nsPartDesc *desc )
{
	m_desc = desc;
	m_partTime = 1.0f / desc->m_count;
	m_timeLeft = 0;
	m_emmit = false;
	m_selfDraw = false;
	m_relPos = false;
}	

//---------------------------------------------------------
// nsPartState::Loop:
//---------------------------------------------------------
void nsPartState::Loop( float time )
{
	if ( !m_emmit ) return;
	
	m_timeLeft -= time;
	if ( m_timeLeft <= 0 )
	{
		m_timeLeft += m_partTime;
		EmitPart();
	}
}

//---------------------------------------------------------
// nsPartState::EmitPart:
//---------------------------------------------------------
void nsPartState::EmitPart()
{
	particle_t *p = g_partManager->m_partCtrl.CreatePart( this );
	if ( p )
	{
		m_desc->CalcPos( p->pos );
		if ( !m_relPos ) p->pos += m_pos;
		m_desc->CalcVel( p->vel );

		p->grav = m_desc->CalcGravity();
		p->scale = m_desc->CalcSizeScale();
		p->angle = m_desc->CalcAngle();
		p->lifeVel = m_desc->CalcLifeVel();
		p->angleRot = m_desc->CalcRotVel();
		p->life = 1;
	}
}