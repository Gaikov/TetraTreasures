// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartState.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_PartState_H_
#define	_PartState_H_

#include "PartDesc.h"

class nsPartState
{
friend class nsPartManager;

public:
	nsPartState();

	void		SetPos( const nsVec2 &pos ) { m_pos = pos; }
	void		SetEmmit( bool emmit ) { m_emmit = emmit; }
	void		SetSelfDraw( bool selfDraw ) { m_selfDraw = selfDraw; }
	void		SetRelPos( bool relPos ) { m_relPos = relPos; }
	void		MakeBlast();
	void		DrawParticles();
	

private:
	nsPartDesc	*m_desc;
	nsVec2		m_pos;
	float		m_partTime;
	float		m_timeLeft;
	bool		m_emmit;
	bool		m_selfDraw;
	bool		m_relPos;		//частицы привязаны к позиции

private:
	void		Init( nsPartDesc *desc );
	void		Loop( float time );
	void		EmitPart();
};

#endif	//_PartState_H_