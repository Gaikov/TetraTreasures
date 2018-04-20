// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file LocalMgr.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "LocalMgr.h"
#include "FontManager.h"

nsLocalMgr *g_local = 0;

//---------------------------------------------------------
// nsLocalMgr::nsLocalMgr:
//---------------------------------------------------------
nsLocalMgr::nsLocalMgr() :
	m_valid( true )
{

}

//---------------------------------------------------------
// nsLocalMgr::~nsLocalMgr:
//---------------------------------------------------------
nsLocalMgr::~nsLocalMgr()
{

}

//---------------------------------------------------------
// nsLocalMgr::Init:
//---------------------------------------------------------
bool nsLocalMgr::Init()
{
	if ( !g_local )
	{
		g_local = new nsLocalMgr;
		if ( !g_local->m_valid )
		{
			delete g_local;
			g_local = 0;
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------
// nsLocalMgr::Release:
//---------------------------------------------------------
void nsLocalMgr::Release()
{
	if ( g_local )
	{
		delete g_local;
		g_local = 0;
	}
}

//---------------------------------------------------------
// nsLocalMgr::GetFont:
//---------------------------------------------------------
nsFont* nsLocalMgr::GetFont( const char *fontID )
{
	return g_fntMgr->FontLoad( fontID );
}

//---------------------------------------------------------
// nsLocalMgr::GetStr:
//---------------------------------------------------------
const char*	nsLocalMgr::GetStr( const char* strID )
{
	return strID;
}
