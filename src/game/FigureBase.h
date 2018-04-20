// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FigureBase.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FigureBase_H_
#define	_FigureBase_H_

#include "common.h"
#include "CorePG/Singl.h"
#include "CorePG/Spline2.h"

struct figCell_t
{
	char		cell;
	int			type;
	nsVec2		pos;
	
	//rotation
	nsSpline2	spline;
	nsVec2		vel;		//стартовая скорость
	nsPartState	*ps;
};

//---------------------------------------------------------
// nsFigure:
//---------------------------------------------------------
class nsFigure
{
friend class nsFigureBase;

public:
	figCell_t&	GetCell( int x, int y ) { return rows[y][x]; }
	int			GetWidth() { return colCount; }
	int			GetHeight() { return rowCount; }
	int			GetCellCount() { return cellCount; }

protected:
	typedef std::vector<figCell_t>	row_t;
	typedef std::vector<row_t>		rows_t;

protected:
	rows_t	rows;
	int		rowCount;
	int		colCount;
	int		cellCount;
};

//---------------------------------------------------------
// nsFigureBase: 
//---------------------------------------------------------
class nsFigureBase : public nsSingl<nsFigureBase>
{
public:
	nsFigure*			GetFigure( int idx );
	int					GetFigureCount();

	const nsImageView&	GetTypeView( int idx );
	int					GetTypeCount();

public:	//HACK:
	nsFigureBase();
	~nsFigureBase();

private:
	typedef std::vector<nsFigure>		figureList_t;
	typedef std::vector<nsImageView>	typeList_t;
	
	figureList_t						m_list;
	typeList_t							m_typeList;

private:
	bool				ParseFigure( script_state_t *ss, nsFigure &fv );
};

extern nsFigureBase	*g_figBase;

#endif //FigureBase_H_