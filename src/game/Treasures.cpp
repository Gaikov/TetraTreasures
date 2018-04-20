// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Treasures.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "Treasures.h"
#include "FieldParams.h"
#include "FigureBase.h"

#define COMBO_TIME	2.0f

nsTreasures	*g_tres = 0;

//---------------------------------------------------------
// nsTreasures::nsTreasures:
//---------------------------------------------------------
nsTreasures::nsTreasures()
{
	g_tres = this;
	m_partDesc.Parse( "scripts/part_tres.txt" );
	m_bowl = nsImageView( "textures/bowl.png", nsVec2( 0, 30 ), nsVec2( 136, 34 ) );
	m_bowlParams.halfSize = m_bowl.GetSize().x * 0.5f;
	m_bowlParams.pos.y = 440;
	m_parts.SetData( &m_bowlParams );
	m_partCatch.Parse( "scripts/part_catch.txt" );
	m_sndCatch = Sound_Load( "sounds/catch.ogg" );
	
	m_fontPoints = g_fntMgr->FontLoad( "fonts/points.txt" );
	m_imgPoints = nsImageView( "textures/points.png", nsVec2( 0, 0 ), nsVec2( 64, 32 ) );
	
	m_fontCombo = g_fntMgr->FontLoad( "fonts/combo.txt" );
	m_comboSnd = Sound_Load( "sounds/combo.ogg" );

	m_valid = true;
}

//---------------------------------------------------------
// nsTreasures::~nsTreasures:
//---------------------------------------------------------
nsTreasures::~nsTreasures()
{
	g_tres = 0;
}

//---------------------------------------------------------
// nsTreasures::NewGame:
//---------------------------------------------------------
void nsTreasures::NewGame()
{
	if ( m_parts.FetchBegin() )
	{
		part_t	*p;
		while ( p = m_parts.Fetch() )
			g_partManager->StateRemove( p->ps );
	}

	m_parts.FreeAll();
	m_points.FreeAll();
	g_gameStat.m_score = 0;
	m_combo = false;
}

//---------------------------------------------------------
// nsTreasures::SetCompo:
//---------------------------------------------------------
void nsTreasures::SetCompo( int mul )
{
	m_mul = mul >= 1 ? mul : 1;
	if ( m_mul > 1 )
	{
		m_combo = true;
		m_comboTime = COMBO_TIME;
		m_comboText.Format( "COMBO %iX", mul );
		Sound_Play( m_comboSnd );
	}
}

//---------------------------------------------------------
// nsTreasures::BreakStart:
//---------------------------------------------------------
void nsTreasures::BreakStart( float velStart, float velStep )
{
	m_velStart = velStart;
	m_velStep = velStep;
	m_velCurr = m_velStart;
}

//---------------------------------------------------------
// nsTreasures::BreakBox:
//---------------------------------------------------------
#define ANGLE_START	(M_PI2 + M_PI / 7.0f * 3.0f)
#define ANGLE_STEP  (M_PI / 21.0f)

void nsTreasures::BreakBox( int cellX, int cellY, int type )
{
	float	angle = ANGLE_START;
	
	for ( int i = 0; i < 4; ++i )
	{
		part_t	*p = m_parts.CreatePart();
		if ( p )
		{
			p->dead = false;
			p->pos.x = Field_PosXCenter( cellX );
			p->pos.y = Field_PosYCenter( cellY );
			p->vel.x = sinf( angle );
			p->vel.y = cosf( angle );
			p->vel *= m_velCurr;
			p->type = type;
			p->ps = g_partManager->StateCreate( &m_partDesc );
			p->ps->SetPos( p->pos );
			p->ps->SetEmmit( true );
			angle += ANGLE_STEP;
			m_velCurr += m_velStep;
		}
	}
}

//---------------------------------------------------------
// nsTreasures::OnMouseMove:
//---------------------------------------------------------
void nsTreasures::OnMouseMove( const nsVec2 &mouse )
{
	m_bowlParams.pos.x = mouse.x;
	float	halfX = m_bowlParams.halfSize;
	Math_Clamp( m_bowlParams.pos.x, FIELD_X + halfX, FIELD_RIGHT - halfX );
}

//---------------------------------------------------------
// nsTreasures::Loop:
//---------------------------------------------------------
void nsTreasures::Loop()
{
	if ( m_parts.FetchBegin() )
	{
		part_t	*p;
		while ( p = m_parts.Fetch() )
		{
			p->vel.y += 300.0f * g_frameTime;
			nsVec2	prevPos = p->pos;
			p->pos += p->vel * g_frameTime;
			if ( p->pos.x <= FIELD_X || p->pos.x >= FIELD_RIGHT )
				p->vel.x = -p->vel.x;
			
			
			if ( p->pos.y >= m_bowlParams.pos.y && prevPos.y < m_bowlParams.pos.y 
				&& p->pos.x >= m_bowlParams.pos.x - m_bowlParams.halfSize 
				&& p->pos.x <= m_bowlParams.pos.x + m_bowlParams.halfSize )
			{
				g_partManager->StateRemove( p->ps );
				p->dead = true;
				nsPartState	*ps = g_partManager->StateCreate( &m_partCatch );
				ps->SetPos( p->pos );
				ps->MakeBlast();
				g_partManager->StateRemove( ps );
				if ( m_sndCatch )
					m_sndCatch->Play();

				int	points;
				if ( m_mul > 1 )
					points =  m_mul * 10;
				else
					points = m_mul * 5;
				g_gameStat.m_score += points;

				partPoints_t	*pt = m_points.CreatePart();
				if ( pt )
				{
					pt->pos = p->pos;
					pt->points = points;
					pt->life = 1;
				}
			}
			else if ( p->pos.y > 500 )
			{
				g_partManager->StateRemove( p->ps );
				p->dead = true;
			}
			else
				p->ps->SetPos( p->pos );
		}
	}
	m_parts.Move( g_frameTime );
	m_points.Move( g_frameTime );

	if ( m_combo )
	{
		m_comboTime -= g_frameTime;
		if ( m_comboTime <= 0 )
			m_combo = false;
	}
}

//---------------------------------------------------------
// nsTreasures::Draw:
//---------------------------------------------------------
void nsTreasures::Draw()
{
	if ( m_parts.FetchBegin() )
	{
		nsVec2	size( FIELD_CELL * 0.5f, FIELD_CELL * 0.5f );
		size.ToInt();
		
		part_t	*p;
		while ( p = m_parts.Fetch() )
		{
			const nsImageView	&img = g_figBase->GetTypeView( p->type );
			nsVec2	pos = p->pos;
			pos.ToInt();
			img.Draw( pos, size, 0, nsColor::white, ALIGN_CENTER );
		}
	}

	m_bowl.Draw( m_bowlParams.pos, m_bowl.GetSize(), 0, nsColor::white, ALIGN_HORZ_CENTER );

	TRenderer *r = TRenderer::GetInstance();
	if ( m_points.FetchBegin() )
	{
		partPoints_t	*p;
		nsString		text;
		nsVec2			pos;
		while ( p = m_points.Fetch() )
		{
			text.Format( "+%i", p->points );
			nsColor	c( 1, 1, 1, p->life );
			nsColor	c2( 0, 0, 0, p->life );
			
			pos = p->pos;
			pos.ToInt();

			r->SetBlendMode( TRenderer::kBlendAdditiveAlpha );
			m_imgPoints.Draw( pos, m_imgPoints.GetSize(), 0, c, ALIGN_CENTER );
			r->SetBlendMode( TRenderer::kBlendNormal );
			Font_DrawAligned( m_fontPoints, text, pos, ALIGN_CENTER, nsVec2( 1, 1 ), c2 );
		}
	}

	if ( m_combo )
	{
		float	s = 1 + COMBO_TIME - m_comboTime;
		nsVec2	pos( FIELD_CENTER_X, 100 );
		pos.ToInt();
		nsColor	c( 1, 1, 1, m_comboTime / COMBO_TIME );

		Font_DrawAligned( m_fontCombo, m_comboText, pos, ALIGN_CENTER, nsVec2( s, s ), c );
	}
}