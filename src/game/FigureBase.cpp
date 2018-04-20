// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FigureBase.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "FigureBase.h"
#include "CorePG/log.h"

nsFigureBase	*g_figBase = 0;

//---------------------------------------------------------
// nsFigureBase::nsFigureBase: 
//---------------------------------------------------------
nsFigureBase::nsFigureBase()
{
	LogPrintf( PRN_ALL, "...init figures base\n" );

	nsParseFile	pf;
	script_state_t	*ss = pf.BeginFile( "scripts/fig_base.txt" );
	if ( !ss || !ps_block_begin( ss, "figure" ) )
	{
		LogPrintf( PRN_ALL, "WARNING: can't parse figure base" );
		return;
	}

	do 
	{
		nsFigure	fv;
		if ( ParseFigure( ss, fv ) )
			m_list.push_back( fv );
	}
	while( ps_block_next( ss ) );

	LogPrintf( PRN_ALL, "...%i figures parsed\n", m_list.size() );

	m_typeList.push_back( nsImageView( "textures/cells.png", nsVec2( 0, 0 ), nsVec2( 25, 25 ) ) );
	m_typeList.push_back( nsImageView( "textures/cells.png", nsVec2( 25, 0 ), nsVec2( 25, 25 ) ) );
	m_typeList.push_back( nsImageView( "textures/cells.png", nsVec2( 50, 0 ), nsVec2( 25, 25 ) ) );
	m_typeList.push_back( nsImageView( "textures/cells.png", nsVec2( 75, 0 ), nsVec2( 25, 25 ) ) );
	m_typeList.push_back( nsImageView( "textures/cells.png", nsVec2( 0, 25 ), nsVec2( 25, 25 ) ) );
	m_typeList.push_back( nsImageView( "textures/cells.png", nsVec2( 25, 25 ), nsVec2( 25, 25 ) ) );
	
	m_valid = true;
	g_figBase = this;
}

//---------------------------------------------------------
// nsFigureBase::~nsFigureBase: 
//---------------------------------------------------------
nsFigureBase::~nsFigureBase()
{
	g_figBase = 0;
}

//---------------------------------------------------------
// nsFigureBase::GetFigure: 
//---------------------------------------------------------
nsFigure* nsFigureBase::GetFigure( int idx )
{
	if ( idx < 0 || idx >= (int)m_list.size() ) return 0;
	return &m_list[idx];
}

//---------------------------------------------------------
// nsFigureBase::GetFigureCount: 
//---------------------------------------------------------
int	nsFigureBase::GetFigureCount()
{
	return m_list.size();
}

//---------------------------------------------------------
// nsFigureBase::GetTypeView:
//---------------------------------------------------------
const nsImageView&	nsFigureBase::GetTypeView( int idx )
{
	assert( idx >= 0 && idx < (int)m_typeList.size() );
	return m_typeList[idx];
}

//---------------------------------------------------------
// nsFigureBase::GetTypeCount:
//---------------------------------------------------------
int nsFigureBase::GetTypeCount()
{
	return (int)m_typeList.size();
}

//---------------------------------------------------------
// nsFigureBase::ParseFigure: 
//---------------------------------------------------------
bool nsFigureBase::ParseFigure( script_state_t *ss, nsFigure &fv )
{
	if ( !ps_var_begin( ss, "row" ) ) return false;

	fv.colCount = fv.rowCount = 0;
	fv.cellCount = 0;
	int	maxCols = 0;
	figCell_t	defCell = { ' ', 0 };
	
	do 
	{
		char *row = ps_var_str( ss );
		if ( row )
		{
			int	currRow = fv.rows.size();

			fv.rows.resize( currRow + 1 );
			if ( maxCols < (int)strlen( row ) )
				maxCols = strlen( row );

			fv.rows[currRow].resize( maxCols, defCell );
			for ( int i = 0; *row; ++i, ++row )
			{
				if ( *row != ' ' )
					fv.cellCount ++;
				fv.rows[currRow][i].cell = *row;
			}
		}
	}
	while( ps_var_next( ss ) );

	fv.colCount = maxCols;
	fv.rowCount = fv.rows.size();

	for ( int i = 0; i < fv.rowCount; ++i )
		fv.rows[i].resize( maxCols, defCell );

	return fv.rows.size() > 0;
}



