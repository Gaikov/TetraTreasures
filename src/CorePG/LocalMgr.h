// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file LocalMgr.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_LocalMgr_H_
#define	_LocalMgr_H_

#include "Font.h"

class nsLocalMgr
{
public:
	static bool Init();
	static void Release();

	void		AddLocalDesc( const char *fileName );

	int			LocGetCount();
	void		LocSetCurrent( int loc );

	nsFont*		GetFont( const char *fontID );
	const char*	GetStr( const char* strID );

private:
	bool		m_valid;

private:
	nsLocalMgr();
	~nsLocalMgr();
};

extern nsLocalMgr *g_local;

#endif	//_LocalMgr_H_