// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuCtrlStyle.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuCtrlStyle.h"

//---------------------------------------------------------
// nsMenuCtrlStyle::Parse:
//---------------------------------------------------------
bool nsMenuCtrlStyle::Parse( script_state_t *ss )
{
	m_id = ps_get_str( ss, "id", "none" );
	return true;
}
