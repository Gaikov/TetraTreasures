// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Align.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "Align.h"
#include <pf/str.h>

//---------------------------------------------------------
// Align_ParseVert:
//---------------------------------------------------------
uint Align_ParseVert( script_state_t *ss )
{
	str	s = ps_get_str( ss, "v_align", "bottom" );
	if ( s == "center" )
		return ALIGN_VERT_CENTER;
	else if ( s == "top" )
		return ALIGN_VERT_TOP;

	return ALIGN_VERT_BOTTOM;
}

//---------------------------------------------------------
// Align_ParseHorz:
//---------------------------------------------------------
uint Align_ParseHorz( script_state_t *ss )
{
	str	s = ps_get_str( ss, "h_align", "left" );
	if ( s == "center" )
		return ALIGN_HORZ_CENTER;
	else if ( s == "right" )
		return ALIGN_HORZ_RIGHT;

	return ALIGN_HORZ_LEFT;
}

//---------------------------------------------------------
// Align_CalcSizeOffs:
//---------------------------------------------------------
nsVec2 Align_CalcSizeOffs( const nsVec2 &size, uint align )
{
	uint	vert = Align_GetVert( align );
	uint	horz = Align_GetHorz( align );

	nsVec2	res;

	if ( vert == ALIGN_VERT_CENTER )
		res.y = size.y * 0.5f;
	else if ( vert == ALIGN_VERT_TOP )
		res.y = size.y;
	else
		res.y = 0;

	if ( horz == ALIGN_HORZ_CENTER )
		res.x = size.x * 0.5f;
	else if ( horz == ALIGN_HORZ_RIGHT )
		res.x = size.x;
	else
		res.x = 0;

	return res;
}
