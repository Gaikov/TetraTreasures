// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuInGame.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuInGame.h"
#include "FigureBase.h"
#include "Field.h"
#include "Treasures.h"
#include <pf/event.h>

nsGameStat	g_gameStat;

//---------------------------------------------------------
// nsMenuInGame::nsMenuInGame:
//---------------------------------------------------------
nsMenuInGame::nsMenuInGame( const char *id ) :
	nsMenuWnd( id )
{
	m_currFig = &m_fig1;
	m_nextFig = &m_fig2;

	m_placeYes = nsImageView( "textures/cells.png", nsVec2( 0, 64 ), nsVec2( 25, 25 ) );
	m_placeNo = nsImageView( "textures/cells.png", nsVec2( 25, 64 ), nsVec2( 25, 25 ) );
}

//---------------------------------------------------------
// nsMenuInGame::~nsMenuInGame:
//---------------------------------------------------------
nsMenuInGame::~nsMenuInGame()
{
	
}

//---------------------------------------------------------
// nsMenuInGame::OnCtrlEvent:
//---------------------------------------------------------
bool nsMenuInGame::OnCtrlEvent( nsMenuControl *ctrl, const char *msg )
{
	if ( StrEqual( msg, "button_click" ) )
	{
		if ( StrEqual( ctrl->GetID(), "ID_MENU" ) )
		{
			g_menu->WndActivate( "IDM_ESC" );
			return true;
		}
		else if ( StrEqual( ctrl->GetID(), "ID_ONLINE" ) )
		{
			TPlatform::GetInstance()->OpenBrowser( ONLINE_LINK );
			return true;
		}
	}

	return false;
}

//---------------------------------------------------------
// nsMenuInGame::Loop:
//---------------------------------------------------------
void nsMenuInGame::Loop( float time )
{
	nsMenuWnd::Loop( time );
	m_figRot.Loop( time );
	g_tres->Loop();

	if ( m_nextFigure )
	{
		if ( !g_tres->IsActive() )
		{
			if ( !g_field->CheckStep( m_nextFig ) )
			{
				g_menu->WndActivate( "IDM_SCORE" );
				return;
			}

			NextFigure();
			CalcFigureCell();
			m_figCanPlace = g_field->CheckPlace( m_figCellX, m_figCellY, m_currFig );
			m_nextFigure = false;
		}
	}
	
	g_gameStat.m_time += time;
	UpdateTime();
	if ( m_prevScore != g_gameStat.m_score )
	{
		m_prevScore = g_gameStat.m_score;
		UpdateScore();
	}
}

//---------------------------------------------------------
// nsMenuInGame::Draw:
//---------------------------------------------------------
void nsMenuInGame::Draw()
{
	nsMenuWnd::Draw();
	g_field->Draw();

	DrawNextFigure();

	if ( !g_tres->IsActive() )
	{
		DrawPlace( m_figCanPlace );
		m_figRot.Draw();
	}

	g_tres->Draw();
	g_partManager->DrawAll();
}

//---------------------------------------------------------
// nsMenuInGame::OnMouseMove:
//---------------------------------------------------------
void nsMenuInGame::OnMouseMove( float x, float y )
{
	nsMenuWnd::OnMouseMove( x, y );

	

	nsVec2	pos( x, y );
	g_tres->OnMouseMove( pos );

	nsVec2	s = m_currFig->CalcSize() * 0.5f;
	Math_Clamp( pos.x, FIELD_X + s.x, FIELD_RIGHT - s.x );
	Math_Clamp( pos.y, FIELD_Y + s.y, FIELD_BOTTOM - s.y );
	m_figRot.SetPos( pos );
	if ( CalcFigureCell() )
		m_figCanPlace = g_field->CheckPlace( m_figCellX, m_figCellY, m_currFig );
}

//---------------------------------------------------------
// nsMenuInGame::OnLButtonDown:
//---------------------------------------------------------
void nsMenuInGame::OnLButtonDown( float x, float y )
{
	nsMenuWnd::OnLButtonDown( x, y );

	nsVec2	pos( x, y );
	if ( !g_tres->IsActive() && Field_PosInside( pos ) )
	{
		if ( g_field->CheckPlace( m_figCellX, m_figCellY, m_currFig ) )
		{
			g_field->FigurePlace( m_figCellX, m_figCellY, m_currFig );
			m_nextFigure = true;
		}
	}
}

//---------------------------------------------------------
// nsMenuInGame::OnRButtonDown:
//---------------------------------------------------------
void nsMenuInGame::OnRButtonDown( float x, float y )
{
	nsMenuWnd::OnRButtonDown( x, y );

	nsVec2	pos( x, y );
	if ( !g_tres->IsActive() && Field_PosInside( pos ) )
	{
		m_figRot.Rotate();
		CalcFigureCell();
		m_figCanPlace = g_field->CheckPlace( m_figCellX, m_figCellY, m_currFig );
	}
}

//---------------------------------------------------------
// nsMenuInGame::OnKeyDown:
//---------------------------------------------------------
void nsMenuInGame::OnKeyDown( int key, bool rept )
{
	if ( key == TEvent::kEscape )
		g_menu->WndActivate( "IDM_ESC" );
	else
		nsMenuWnd::OnKeyDown( key, rept );
}

//---------------------------------------------------------
// nsMenuInGame::NewGame:
//---------------------------------------------------------
void nsMenuInGame::NewGame()
{
	m_nextFigure = false;
	g_tres->NewGame();
	NextFigure();
	NextFigure();
	g_field->Clear();
	m_figCanPlace = false;
	m_figCellX = m_figCellY = 0;

	m_prevScore = 0;
	g_gameStat.m_time = 0;

	UpdateScore();
	UpdateTime();
}

//---------------------------------------------------------
// nsMenuInGame::NextFigure:
//---------------------------------------------------------
void nsMenuInGame::NextFigure()
{
	std::swap( m_currFig, m_nextFig );
	int	idx = rand() % g_figBase->GetFigureCount();
	if ( m_currFig->GetFigure() == g_figBase->GetFigure( idx ) )
		idx = (idx + 1) % g_figBase->GetFigureCount();
	m_nextFig->SetFigure( g_figBase->GetFigure( idx ) );
	m_figRot.SetView( m_currFig );
}

//---------------------------------------------------------
// nsMenuInGame::DrawPlace:
//---------------------------------------------------------
void nsMenuInGame::DrawPlace( bool yes )
{
	nsImageView	&img = yes ? m_placeYes : m_placeNo;

	nsVec2	pos;
	pos.x = Field_PosX( m_figCellX );
	pos.y = Field_PosY( m_figCellY );

	for ( int x = 0; x < m_currFig->GetWidth(); ++x )
		for ( int y = 0; y < m_currFig->GetHeight(); ++y )
		{
			figCell_t &cell = m_currFig->GetCell( x, y );
			if ( cell.cell != ' ' )
			{
				nsVec2	p;
				p.x = float(x * FIELD_CELL);
				p.y = float(y * FIELD_CELL);
				p += pos;
				img.Draw( p, m_placeYes.GetSize(), 0, nsColor( 1, 1, 1, 1 ) );
			}
		}
}

//---------------------------------------------------------
// nsMenuInGame::DrawNextFigure:
//---------------------------------------------------------
void nsMenuInGame::DrawNextFigure()
{
	nsVec2	pos( 542, 270 );
	pos -= m_nextFig->CalcCenter();
	pos.ToInt();
	m_nextFig->Draw( pos );
}

//---------------------------------------------------------
// nsMenuInGame::CalcFigureCell:
//---------------------------------------------------------
bool nsMenuInGame::CalcFigureCell()
{
	nsVec2	center = m_currFig->CalcCenter();
	nsVec2 pos = m_figRot.GetPos() - center;

	int	cellX = m_figCellX;
	int	cellY = m_figCellY;

	m_figCellX = Field_CellX( pos.x + FIELD_CELL * 0.5f );
	m_figCellY = Field_CellY( pos.y + FIELD_CELL * 0.5f );

	return cellX != m_figCellX || cellY != m_figCellY;
}

//---------------------------------------------------------
// nsMenuInGame::UpdateTime:
//---------------------------------------------------------
void nsMenuInGame::UpdateTime()
{
	nsStaticText	*t = GetStaticByID( "IDT_TIME" );
	if ( t )
	{
		nsString	time;
		Time_Format( time.AsChar(), g_gameStat.m_time );
		t->SetText( time );
	}
}

//---------------------------------------------------------
// nsMenuInGame::UpdateScore:
//---------------------------------------------------------
void nsMenuInGame::UpdateScore()
{
	nsStaticText	*t = GetStaticByID( "IDT_SCORE" );
	if ( t )
	{
		nsString	score;
		score.Format( "$%i", g_gameStat.m_score );
		t->SetText( score );
	}	
}

//---------------------------------------------------------
// nsMenuInGame::OnChildEvent:
//---------------------------------------------------------
bool nsMenuInGame::OnChildEvent( nsMenuWnd *wnd, const char *msg )
{
	if ( StrEqual( msg, "CLICK_NEW_GAME" ) )
	{
		NewGame();
		return true;
	}
	return false;
}