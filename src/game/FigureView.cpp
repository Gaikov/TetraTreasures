// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FigureView.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "FigureView.h"
#include "FieldParams.h"

//---------------------------------------------------------
// nsFigureView::nsFigureView: 
//---------------------------------------------------------
nsFigureView::nsFigureView() :
	m_figure( 0 ),
	m_rotation( 0 )
{

}

//---------------------------------------------------------
// nsFigureView::SetFigure: 
//---------------------------------------------------------
void nsFigureView::SetFigure( nsFigure *f )
{
	m_figure = f;

	if ( m_figure )
	{
		for ( int x = 0; x < f->GetWidth(); ++x )
			for ( int y = 0; y < f->GetHeight(); ++y )
			{
				figCell_t	&cell = m_figure->GetCell( x, y );
				if ( cell.cell != ' ' )
					cell.type = (rand() % g_figBase->GetTypeCount());
			}
	}
}

//---------------------------------------------------------
// nsFigureView::SetRotation: 
//---------------------------------------------------------
void nsFigureView::SetRotation( int r )
{
	m_rotation = abs( r ) % 4;
}

//---------------------------------------------------------
// nsFigureView::GetWidth: 
//---------------------------------------------------------
int	nsFigureView::GetWidth() const
{
	if ( !m_figure ) return 0;

	if ( m_rotation & 1 )
		return m_figure->GetHeight();

	return m_figure->GetWidth();
}

//---------------------------------------------------------
// nsFigureView::GetHeight: 
//---------------------------------------------------------
int	nsFigureView::GetHeight() const
{
	if ( !m_figure ) return 0;

	if ( m_rotation & 1 )
		return m_figure->GetWidth();

	return m_figure->GetHeight();
}

//---------------------------------------------------------
// nsFigureView::GetCell: 
//---------------------------------------------------------
figCell_t& nsFigureView::GetCell( int x, int y ) const
{
	switch ( m_rotation )
	{
	case 0:
		break;
	case 1:
		x = GetWidth() - 1 - x;
		std::swap( x, y );
		break;
	case 2:
		y = GetHeight() - 1 - y;
		x = GetWidth() - 1 - x;
		break;
	case 3:
		y = GetHeight() - 1 - y;
		std::swap( x, y );
		break;
	}

	return m_figure->GetCell( x, y );
}

//---------------------------------------------------------
// nsFigureView::CalcCenter:
//---------------------------------------------------------
nsVec2 nsFigureView::CalcCenter() const
{
	nsVec2	center;
	center.x = GetWidth() * FIELD_CELL * 0.5f;
	center.y = GetHeight() * FIELD_CELL * 0.5f;
	return center;
}

//---------------------------------------------------------
// nsFigureView::CalcSize:
//---------------------------------------------------------
nsVec2 nsFigureView::CalcSize() const
{
	nsVec2	size;
	size.x = float( GetWidth() * FIELD_CELL );
	size.y = float( GetHeight() * FIELD_CELL );
	return size;
}

//---------------------------------------------------------
// nsFigureView::Draw:
//---------------------------------------------------------
void nsFigureView::Draw( const nsVec2 &pos )
{
	int	w = GetWidth();
	int h = GetHeight();

	for ( int x = 0; x < w; ++x )
		for ( int y = 0; y < h; ++y )
		{
			const figCell_t &cell = GetCell( x, y );
			if ( cell.cell != ' ' )
			{
				nsVec2	p;
				p.x = float( x * FIELD_CELL );
				p.y = float( y * FIELD_CELL );

				const nsImageView &img = g_figBase->GetTypeView( cell.type );
				img.Draw( pos + p, nsVec2( FIELD_CELL, FIELD_CELL ) );
			}
		}
}

