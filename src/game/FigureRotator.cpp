// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FigureRotator.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "FigureRotator.h"
#include "FieldParams.h"

#define ROT_TIME	0.3f
#define ROT_VEL		1000.0f

//---------------------------------------------------------
// nsFigureRotator::nsFigureRotator:
//---------------------------------------------------------
nsFigureRotator::nsFigureRotator() :
	m_fv( 0 ),
	m_rotate( false )
{
	m_partDesc.Parse( "scripts/part_figure.txt" );
	m_sndStart = Sound_Load( "sounds/rotate.ogg" );
	m_sndEnd = Sound_Load( "sounds/rotate_end.ogg" );
}


//---------------------------------------------------------
// nsFigureRotator::SetView:
//---------------------------------------------------------
void nsFigureRotator::SetView( nsFigureView *fv )
{
	if ( !fv || !fv->GetFigure() )
	{
		m_fv = 0;
		return;
	}

	if ( m_rotate )	StopRotate();

	m_fv = fv;
	m_cells.resize( m_fv->GetFigure()->GetCellCount() );
	ForceCellsPos();
}

//---------------------------------------------------------
// nsFigureRotator::Loop:
//---------------------------------------------------------
void nsFigureRotator::Loop( float time )
{
	if ( !m_rotate ) return;

	cellList_t::iterator	it;

	m_rotTime += time;
	if ( m_rotTime >= ROT_TIME )
	{
		StopRotate();
		ForceCellsPos();
		Sound_Play( m_sndEnd );
	}
	else
	{
		for ( it = m_cells.begin(); it != m_cells.end(); ++it )
		{
			figCell_t	*cell = *it;
			cell->spline.CalcPos( m_rotTime, cell->pos );
			cell->ps->SetPos( cell->pos + m_pos + nsVec2( FIELD_CELL, FIELD_CELL ) * 0.5f );
		}
	}
}

//---------------------------------------------------------
// nsFigureRotator::SetPos:
//---------------------------------------------------------
void nsFigureRotator::SetPos( const nsVec2 &pos )
{
	m_pos = pos;
}

//---------------------------------------------------------
// nsFigureRotator::Rotate:
//---------------------------------------------------------
void nsFigureRotator::Rotate()
{
	if ( !m_fv ) return;

	m_fv->SetRotation( m_fv->GetRotation() + 1 );
	if ( m_fv->GetWidth() == 1 && m_fv->GetHeight() == 1 ) return;

	Sound_Play( m_sndStart );
	m_rotate = true;
	m_rotTime = 0;

	nsVec2	center;
	center.x = m_fv->GetWidth() * FIELD_CELL * 0.5f;
	center.y = m_fv->GetHeight() * FIELD_CELL * 0.5f;

	nsVec2	halfCell = nsVec2( FIELD_CELL, FIELD_CELL ) * 0.5f;

	for ( int x = 0; x < m_fv->GetWidth(); ++x )
		for ( int y = 0; y < m_fv->GetHeight(); ++y )
		{
			figCell_t	&cell = m_fv->GetCell( x, y );
			if ( cell.cell != ' ' )
			{
				nsVec2	pos2, vel2;
				pos2.x = float(x * FIELD_CELL) - center.x;
				pos2.y = float(y * FIELD_CELL) - center.y;
				vel2 = pos2;
				vel2 += halfCell;
				vel2.Invert();
				vel2.Norm();
				vel2 *= ROT_VEL;
				cell.spline.SetSegment( cell.pos, cell.vel, pos2, vel2, ROT_TIME );

				if ( !cell.ps )
				{
					cell.ps = g_partManager->StateCreate( &m_partDesc );
					cell.ps->SetPos( cell.pos + halfCell );
					cell.ps->SetEmmit( true );
				}
			}
		}
}

//---------------------------------------------------------
// nsFigureRotator::Draw:
//---------------------------------------------------------
void nsFigureRotator::Draw()
{
	if ( !m_fv ) return;

	cellList_t::iterator	it;
	for ( it = m_cells.begin(); it != m_cells.end(); ++it )
	{
		figCell_t	*cell = *it;

		nsVec2	pos = cell->pos + m_pos;
		pos.ToInt();
		const nsImageView	&img = g_figBase->GetTypeView( cell->type );
		img.Draw( pos, nsVec2( FIELD_CELL, FIELD_CELL ) );
	}
}

//---------------------------------------------------------
// nsFigureRotator::ForceCellsPos:
//---------------------------------------------------------
void nsFigureRotator::ForceCellsPos()
{
	nsVec2	center;
	center.x = m_fv->GetWidth() * FIELD_CELL * 0.5f;
	center.y = m_fv->GetHeight() * FIELD_CELL * 0.5f;

	int	i = 0;
	for ( int x = 0; x < m_fv->GetWidth(); ++x )
		for ( int y = 0; y < m_fv->GetHeight(); ++y )
		{
			figCell_t	&cell = m_fv->GetCell( x, y );
			if ( cell.cell != ' ' )
			{
				m_cells[i] = &cell;
				cell.pos.x = float(x * FIELD_CELL) - center.x;
				cell.pos.y = float(y * FIELD_CELL) - center.y;
				cell.vel = cell.pos;
				cell.vel += nsVec2( FIELD_CELL, FIELD_CELL ) * 0.5f;
				cell.vel.Norm();
				cell.vel *= ROT_VEL;
				cell.ps = 0;
				i++;
			}
		}
}

//---------------------------------------------------------
// nsFigureRotator::StopRotate:
//---------------------------------------------------------
void nsFigureRotator::StopRotate()
{
	cellList_t::iterator	it;

	for ( it = m_cells.begin(); it != m_cells.end(); ++it )
	{
		figCell_t	*cell = *it;
		g_partManager->StateRemove( cell->ps );
		cell->ps = 0;
	}

	m_rotate = false;
}