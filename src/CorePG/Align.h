// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Align.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Align_H_
#define	_Align_H_

#include "comm_types.h"
#include "Vec2.h"
#include "Parser.h"

#define ALIGN_VERT_BOTTOM	1
#define ALIGN_VERT_TOP		2
#define ALIGN_VERT_CENTER	3
#define ALIGN_HORZ_LEFT		(1 << 2)
#define ALIGN_HORZ_RIGHT	(2 << 2)
#define ALIGN_HORZ_CENTER	(3 << 2)
#define ALIGN_CENTER		(ALIGN_HORZ_CENTER | ALIGN_VERT_CENTER)

uint		Align_ParseVert( script_state_t *ss );
uint		Align_ParseHorz( script_state_t *ss );
nsVec2		Align_CalcSizeOffs( const nsVec2 &size, uint align );

//---------------------------------------------------------
// Align_GetVert:
//---------------------------------------------------------
inline uint Align_GetVert( uint align )
{
	return align & 3;
}

//---------------------------------------------------------
// Align_GetHorz:
//---------------------------------------------------------
inline uint Align_GetHorz( uint align )
{
	return align & (3 << 2);
}

#endif	//_Align_H_