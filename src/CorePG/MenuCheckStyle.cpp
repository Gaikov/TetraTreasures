// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuCheckStyle.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuCheckStyle.h"

//---------------------------------------------------------
// nsMenuCheckStyle::Parse:
//---------------------------------------------------------
bool nsMenuCheckStyle::Parse( script_state_t *ss )
{
	if ( !nsMenuButtonStyle::Parse( ss ) ) return false;

	m_check.Parse( ss, "img_check" );
	return true;
}