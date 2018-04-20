// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file AppInfo.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_AppInfo_H_
#define	_AppInfo_H_

#include "UserInput.h"

//---------------------------------------------------------
// IAppInfo: Некоторая ниформация для ядра (движка) о приложении
//---------------------------------------------------------
struct IAppInfo
{
	virtual bool			Init() = 0;
	virtual void			Release() = 0;
	virtual const char*		GetAppName() = 0;
	virtual void			GetUserInput( IUserInput::list_t &ui ) = 0;
	virtual void			Loop( float frameTime ) = 0;
	virtual void			DrawWorld() = 0;
};

IAppInfo*	App_GetInfo();	//должна быть реализована в приложении (exe)

#endif //_AppInfo_H_