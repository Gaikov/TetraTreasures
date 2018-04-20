// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FieldParams.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "FieldParams.h"

//---------------------------------------------------------
// Field_CellPosCenter:
//---------------------------------------------------------
void Field_CellPosCenter( int x, int y, nsVec2 &pos )
{
	pos.x = Field_PosXCenter( x );
	pos.y = Field_PosYCenter( y );
}

//---------------------------------------------------------
// Field_CellPos:
//---------------------------------------------------------
void Field_CellPos( int x, int y, nsVec2 &pos )
{
	pos.x = Field_PosX( x );
	pos.y = Field_PosY( y );
}

//---------------------------------------------------------
// Field_ClampPos:
//---------------------------------------------------------
void Field_ClampPos( nsVec2 &pos )
{
	Math_Clamp( pos.x, FIELD_X, FIELD_RIGHT );
	Math_Clamp( pos.y, FIELD_Y, FIELD_BOTTOM );
}

//---------------------------------------------------------
// Field_PosInside:
//---------------------------------------------------------
bool Field_PosInside( const nsVec2 &pos )
{
	if ( pos.x < FIELD_X || pos.x > FIELD_RIGHT ) return false;
	if ( pos.y < FIELD_Y || pos.y > FIELD_BOTTOM ) return false;
	return true;
}

//---------------------------------------------------------
// Field_CellX:
//---------------------------------------------------------
int	Field_CellX( float posX )
{
	return int( (posX - FIELD_X) / FIELD_CELL );
}

//---------------------------------------------------------
// Field_CellY:
//---------------------------------------------------------
int	Field_CellY( float posY )
{
	return int( (posY - FIELD_Y) / FIELD_CELL );
}

//---------------------------------------------------------
// Field_PosX:
//---------------------------------------------------------
float	Field_PosX( int cellX )
{
	return (float)int(FIELD_X + cellX * FIELD_CELL);
}

//---------------------------------------------------------
// Field_PosY:
//---------------------------------------------------------
float	Field_PosY( int cellY )
{
	return (float)int(FIELD_Y + cellY * FIELD_CELL);
}

//---------------------------------------------------------
// Field_PosXCenter:
//---------------------------------------------------------
float	Field_PosXCenter( int cellX )
{
	return (float)int(FIELD_X + cellX * FIELD_CELL + FIELD_CELL * 0.5f);
}

//---------------------------------------------------------
// Field_PosYCenter:
//---------------------------------------------------------
float	Field_PosYCenter( int cellY )
{
	return (float)int(FIELD_Y + cellY * FIELD_CELL + FIELD_CELL * 0.5f);
}


