// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuTable.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuTable_H_
#define	_MenuTable_H_

#include "Str.h"
#include "Parser.h"
#include "Color.h"
#include "Vec2.h"
#include "Font.h"
#include <vector>

class nsMenuTable
{
public:
	nsMenuTable();
	virtual ~nsMenuTable();

	bool	Parse( script_state_t *ss );
	bool	Parse( script_state_t *ss, const char *block );
	int		GetRowCount() { return m_rowCount; }
	int		GetColCount() { return (int)m_colList.size(); }
	void	CellSetText( int x, int y, const char *text );
	void	CellSetColor( int x, int y, const nsColor &c );
	void	CellSetScale( int x, int y, const nsVec2 &s );
	void	Draw();

private:
	struct cell_t
	{
		nsVec2		pos;
		nsString	text;
		nsVec2		scale;
		nsColor		color;
		uint		align;
	};

	struct colDesc_t
	{
		float	offs;
		uint	align;
	};

	typedef std::vector<colDesc_t>	colList_t;
	typedef cell_t*					row_t;

private:
	colList_t	m_colList;

	row_t		*m_cells;
	int			m_rowCount;

	nsFont		*m_font;
	nsColor		m_defColor;
	nsVec2		m_defScale;
	nsString	m_defText;
};

#endif	//_MenuTable_H_