// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuTable.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuTable.h"
#include "LocalMgr.h"
#include "StrTools.h"
#include "Align.h"

nsMenuTable::nsMenuTable() :
	m_rowCount( 0 ),
	m_cells( 0 ),
	m_font( 0 )
{

}

//---------------------------------------------------------
// nsMenuTable::~nsMenuTable:
//---------------------------------------------------------
nsMenuTable::~nsMenuTable()
{
	if ( m_cells )
	{
		for ( int i = 0; i < m_rowCount; ++i )
			delete [] m_cells[i];
		delete [] m_cells;
	}
}

//---------------------------------------------------------
// nsMenuTable::Parse:
//---------------------------------------------------------
bool nsMenuTable::Parse( script_state_t *ss )
{
	m_rowCount = (int)fabsf( ps_get_f( ss, "row_count" ) );
	if ( !m_rowCount ) return false;

	m_font = g_local->GetFont( ps_get_str( ss, "font" ) );
	if ( !m_font ) return false;

	ps_get_color( ss, "def_color", m_defColor );
	ps_get_2f( ss, "def_scale", m_defScale );
	m_defText = ps_get_str( ss, "def_text" );

	nsVec2	pos;
	float	rowStep = ps_get_f( ss, "row_step", 10 );
	ps_get_2f( ss, "pos", pos );

	if ( ps_block_begin( ss, "col" ) )
	{
		do 
		{
			colDesc_t	col;
			col.offs = ps_get_f( ss, "offs" );
			col.align = Align_ParseHorz( ss );

			m_colList.push_back( col );
		}
		while( ps_block_next( ss ) );
		ps_block_end( ss );
	}

	if ( !m_colList.size() ) return false;

	m_cells = new row_t[m_rowCount];
	float vertPos = pos.y;
	for ( int i = 0; i < m_rowCount; ++i )
	{
		m_cells[i] = new cell_t[m_colList.size()];

		for ( int j = 0; j < (int)m_colList.size(); ++j )
		{
			cell_t	&cell = m_cells[i][j];

			cell.align = m_colList[j].align;
			cell.color = m_defColor;
			cell.scale = m_defScale;
			cell.text = m_defText;
			cell.pos.x = pos.x + m_colList[j].offs;
			cell.pos.y = vertPos;
		}

		vertPos += rowStep;
	}

	return true;
}

//---------------------------------------------------------
// nsMenuTable::Parse:
//---------------------------------------------------------
bool nsMenuTable::Parse( script_state_t *ss, const char *block )
{
	if ( !StrCheck( block ) ) return false;

	bool	res = false;
	if ( ps_block_begin( ss, block ) )
	{
		res = Parse( ss );
		ps_block_end( ss );
	}

	return res;
}

//---------------------------------------------------------
// nsMenuTable::CellSetText:
//---------------------------------------------------------
void nsMenuTable::CellSetText( int x, int y, const char *text )
{
	if ( x < 0 || x >= GetColCount() ) return;
	if ( y < 0 || y >= GetRowCount() ) return;
	m_cells[y][x].text = text;
}

//---------------------------------------------------------
// nsMenuTable::CellSetColor:
//---------------------------------------------------------
void nsMenuTable::CellSetColor( int x, int y, const nsColor &c )
{
	if ( x < 0 || x >= GetColCount() ) return;
	if ( y < 0 || y >= GetRowCount() ) return;
	m_cells[y][x].color = c;
}

//---------------------------------------------------------
// nsMenuTable::CellSetScale:
//---------------------------------------------------------
void nsMenuTable::CellSetScale( int x, int y, const nsVec2 &s )
{
	if ( x < 0 || x >= GetColCount() ) return;
	if ( y < 0 || y >= GetRowCount() ) return;
	m_cells[y][x].scale = s;
}

//---------------------------------------------------------
// nsMenuTable::Draw:
//---------------------------------------------------------
void nsMenuTable::Draw()
{
	if ( !m_cells ) return;

	for ( int y = 0; y < m_rowCount; ++y )
		for ( int x = 0; x < (int)m_colList.size(); ++x )
		{
			cell_t	&cell = m_cells[y][x];
			Font_DrawAligned( m_font, cell.text, cell.pos, cell.align, cell.scale, cell.color );
		}
}