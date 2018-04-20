// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GameWnd.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "GameWnd.h"
#include "AppInfo.h"
#include <pf/debug.h>
#include <pf/renderer.h>

PFTYPEIMPL_DC( nsGameWnd );

//---------------------------------------------------------
// nsGameWnd::Draw:
//---------------------------------------------------------
void nsGameWnd::Draw()
{
	TRenderer *r = TRenderer::GetInstance();
	r->Begin2d();
	App_GetInfo()->DrawWorld();
	r->End2d();
}