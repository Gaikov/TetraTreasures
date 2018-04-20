// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuEsc.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuEsc_H_
#define	_MenuEsc_H_

#include "common.h"

class nsMenuEsc : public nsMenuWnd
{
public:
	nsMenuEsc( const char *id );

	virtual void OnKeyDown( int key, bool rept );
	virtual bool OnCtrlEvent( nsMenuControl *ctrl, const char *msg );

};

#endif //_MenuEsc_H_