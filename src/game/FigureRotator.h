// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FigureRotator.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FigureRotator_H_
#define	_FigureRotator_H_

#include "FigureView.h"

class nsFigureRotator
{
public:
	nsFigureRotator();

	void			SetView( nsFigureView *fv );
	void			Loop( float time );
	void			SetPos( const nsVec2 &pos );
	const nsVec2&	GetPos() { return m_pos; }
	void			Rotate();
	void			Draw();

private:
	typedef std::vector<figCell_t*>	cellList_t;

private:
	cellList_t		m_cells;
	nsFigureView	*m_fv;
	nsVec2			m_pos;
	
	bool			m_rotate;
	float			m_rotTime;

	nsPartDesc		m_partDesc;

	TSoundRef		m_sndStart;
	TSoundRef		m_sndEnd;

private:
	void			ForceCellsPos();
	void			StopRotate();
};

#endif	//_FigureRotator_H_