// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GameWnd.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_GameWnd_H_
#define	_GameWnd_H_

#include <pf/window.h>

class nsGameWnd : public TWindow
{
	PFTYPEDEF_DC( nsGameWnd, TWindow )
public:
	virtual void Draw();
};

#endif	//_GameWnd_H_