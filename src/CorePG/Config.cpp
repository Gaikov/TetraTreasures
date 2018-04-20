// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Config.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "Config.h"

nsConfig *g_cfg = 0;

//---------------------------------------------------------
// nsConfig::nsConfig:
//---------------------------------------------------------
nsConfig::nsConfig() :
	m_valid( true )
{

}

//---------------------------------------------------------
// nsConfig::~nsConfig:
//---------------------------------------------------------
nsConfig::~nsConfig()
{

}

//---------------------------------------------------------
// nsConfig::Init:
//---------------------------------------------------------
bool nsConfig::Init()
{
	if ( !g_cfg )
	{
		g_cfg = new nsConfig;
		if ( !g_cfg->m_valid )
		{
			delete g_cfg;
			g_cfg = 0;
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------
// nsConfig::Release:
//---------------------------------------------------------
void nsConfig::Release()
{
	if ( g_cfg )
	{
		delete g_cfg;
		g_cfg = 0;
	}
}

//---------------------------------------------------------
// nsConfig::RegVar:
//---------------------------------------------------------
nsVar* nsConfig::RegVar( const char *name, const char *defVal, uint flags /*= 0 */ )
{
	return new nsVar;
}

//---------------------------------------------------------
// nsConfig::RegCmd:
//---------------------------------------------------------
void nsConfig::RegCmd( const char *name, func_t func )
{

}