// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Config.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Config_H_
#define	_Config_H_

#include "Var.h"

#define GVF_SAVABLE	1

typedef void (*func_t)( int argc, const char *argv[] );

class nsConfig
{
public:
	static bool Init();
	static void Release();

	nsVar*		RegVar( const char *name, const char *defVal, uint flags = 0 );
	void		RegCmd( const char *name, func_t func );

private:
	bool		m_valid;

private:
	nsConfig();
	~nsConfig();
};

extern nsConfig *g_cfg;

#endif	//_Config_H_