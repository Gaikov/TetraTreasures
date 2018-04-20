// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FigureView.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FigureView_H_
#define	_FigureView_H_

#include "common.h"
#include "FigureBase.h"

class nsFigureView
{
public:
	nsFigureView();

	void				SetFigure( nsFigure *f );
	nsFigure*			GetFigure() { return m_figure; }
	void				SetRotation( int r );	//0..3
	int					GetRotation() { return m_rotation; }
	int					GetWidth() const;
	int					GetHeight() const;
	figCell_t&			GetCell( int x, int y ) const;
	nsVec2				CalcCenter() const;
	nsVec2				CalcSize() const;
	void				Draw( const nsVec2 &pos );


private:
	nsFigure			*m_figure;
	int					m_rotation;
};

#endif //FigureView_H_