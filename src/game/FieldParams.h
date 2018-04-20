// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FieldParams.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FieldParams_H_
#define	_FieldParams_H_

#include "common.h"

#define FIELD_WIDTH		16
#define FIELD_HEIGHT	16
#define FIELD_CELL		25

#define FIELD_Y float((480 - FIELD_HEIGHT * FIELD_CELL) >> 1)
#define FIELD_X float(FIELD_Y)

#define FIELD_SIZE_X (FIELD_WIDTH * FIELD_CELL)
#define FIELD_SIZE_Y (FIELD_HEIGHT * FIELD_CELL)

#define FIELD_CENTER_X (FIELD_X + FIELD_SIZE_X * 0.5f)
#define FIELD_CENTER_Y (FIELD_Y + FIELD_SIZE_Y * 0.5f)

#define FIELD_RIGHT (FIELD_X + FIELD_SIZE_X)
#define FIELD_BOTTOM (FIELD_Y + FIELD_SIZE_Y)

void	Field_CellPosCenter( int x, int y, nsVec2 &pos );
void	Field_CellPos( int x, int y, nsVec2 &pos );
void	Field_ClampPos( nsVec2 &pos );
bool	Field_PosInside( const nsVec2 &pos );
int		Field_CellX( float posX );
int		Field_CellY( float posY );
float	Field_PosX( int cellX );
float	Field_PosY( int cellY );
float	Field_PosXCenter( int cellX );
float	Field_PosYCenter( int cellY );

#endif	//_FieldParams_H_