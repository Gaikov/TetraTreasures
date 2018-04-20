// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Core.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Core_H_
#define	_Core_H_

struct nsCore
{
	static void RunGame();

private:
	static bool Init();
	static void Release();
};

#endif	//_Core_H_