// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuMain.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuMain.h"
#include "FigureBase.h"
#include "FieldParams.h"

nsMenuMain::nsMenuMain( const char *id ) :
	nsMenuWnd( id ),
	m_backOffs( 0 ),
	m_backAngle( 0 )
{
	m_sprBack.tex = TTexture::Get( "textures/cells_back.png" );
	m_sprBack.useTex = true;
	m_sprBack.size = nsVec2( 640, 480 );
	m_sprBack.color = nsColor::gray;

	m_backSize = nsVec2( 640.0f / 128, 480.0f / 128 );

	m_partBack.Parse( "scripts/part_back.txt" );
	for ( int i = 0; i < 10; ++i )
	{
		part_t	*p = m_parts.CreatePart();
		p->pos.x = Math_Rand( 640 );
		p->pos.y = Math_Rand( 480 );
		p->type = rand() % g_figBase->GetTypeCount();
		p->time = p->maxTime = 0;
		p->nextPos = p->pos;

		p->nextVel.x = Math_Rand( 200 );
		p->nextVel.y = Math_Rand( 200 );
		p->nextVel.Norm();
		p->nextVel *= 200;

		p->ps = g_partManager->StateCreate( &m_partBack );
		p->ps->SetPos( p->pos );
		p->ps->SetEmmit( true );
		p->ps->SetSelfDraw( true );
	}
}

//---------------------------------------------------------
// nsMenuMain::OnCtrlEvent:
//---------------------------------------------------------
bool nsMenuMain::OnCtrlEvent( nsMenuControl *ctrl, const char *msg )
{
	nsString	id = ctrl->GetID();
	if ( StrEqual( msg, "button_click" ) )
	{
		if ( id == "ID_EXIT" )
		{
			TPlatform::GetInstance()->Exit();
			return true;
		}
		else if ( id == "ID_NEW_GAME" )
		{
			if ( m_parent )
				m_parent->OnChildEvent( this, "CLICK_NEW_GAME" );
			Close();
			g_menu->WndActivate( "IDM_ADS" );
			return true;
		}
		else if ( id == "ID_MORE_GAMES" )
		{
			TPlatform::GetInstance()->OpenBrowser( "http://free-casual-game.com" );
			return true;			
		}
		else if ( id == "ID_ONLINE" )
		{
			TPlatform::GetInstance()->OpenBrowser( ONLINE_LINK );
			return true;
		}
	}

	return false;
}

//---------------------------------------------------------
// nsMenuMain::Loop:
//---------------------------------------------------------
void nsMenuMain::Loop( float time )
{
	m_backOffs += time * 0.1f;
	m_backAngle += time;
	m_parts.Move( time );
}

//---------------------------------------------------------
// nsMenuMain::Draw:
//---------------------------------------------------------
void nsMenuMain::Draw()
{
	//back
	nsVec2	offs( m_backOffs, m_backOffs );
	
	float	s = 0.08f * sinf( m_backAngle );
	nsVec2	offs2( s, s );

	TRenderer	*r = TRenderer::GetInstance();
	r->SetTextureMapMode( TRenderer::kMapWrap, TRenderer::kMapWrap );

	//m_sprBack.tex1 = offs + offs2;
	m_sprBack.tex2 = m_backSize;// + offs + offs2;
	RX_DrawSprite( m_sprBack );
	r->SetTextureMapMode( TRenderer::kMapClamp, TRenderer::kMapClamp );

	//parts
	if ( m_parts.FetchBegin() )
	{
		part_t	*p;
		while ( p = m_parts.Fetch() )
		{
			const nsImageView &img = g_figBase->GetTypeView( p->type );
			nsVec2	pos = p->pos;
			pos.ToInt();
			img.Draw( pos, nsVec2( FIELD_CELL, FIELD_CELL ), 0, nsColor::white, ALIGN_CENTER );

			p->ps->DrawParticles();
		}
	}
	
	nsMenuWnd::Draw();
}