// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GameApp.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_GameApp_H_
#define	_GameApp_H_

#include "common.h"

class nsGameApp : public IAppInfo
{
private:
	virtual bool			Init();
	virtual void			Release();
	virtual const char*		GetAppName();
	virtual void			GetUserInput( IUserInput::list_t &ui );
	virtual void			Loop( float frameTime );
	virtual void			DrawWorld();
};

extern nsGameApp	*g_app;

#endif	//_GameApp_H_