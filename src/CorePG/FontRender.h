// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FontRender.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FontRender_H_
#define	_FontRender_H_

#include "comm_types.h"
#include "Vec2.h"
#include "color.h"
#include "RenPatchBuffer.h"

//---------------------------------------------------------
// charView_t:
//---------------------------------------------------------
struct charView_t
{
	nsVec2	texPos;		//позиция символа на текстуре
	nsVec2	texSize;	//размер символа на текстуре
	nsVec2	outSize;	//размер символа при выводе
	nsVec2	outOffs;	//смещение от курсора при выводе
	float	step;		//шаг после вывода
};

//---------------------------------------------------------
// charDrawParams_t:
//---------------------------------------------------------
struct charDrawParams_t
{
	nsVec2	scale;
	nsVec2	offs;
	float	angle;
	nsColor	color;
};

//---------------------------------------------------------
// nsFontRender:
//---------------------------------------------------------
class nsFontRender : public nsRenPatchBuffer
{
public:
	nsFontRender( uint reserveChars );

	void		DrawBegin( const nsVec2 &startPos );
	void		ResetPos( const nsVec2 &pos );
	void		DrawFlush();

	void		AddChar( const charView_t &cv, const nsVec2 &scale, TColor32 color );
	void		AddCharFX( const charView_t &cv, const nsVec2 &scale, const charDrawParams_t &p );
	void		AddStep( float step );

private:
	nsVec2		m_currPos;
	uint		m_countChars;	//текущее кол-во символов в буфере
};

#endif	//_FontRender_H_