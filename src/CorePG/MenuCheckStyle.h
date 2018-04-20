// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuCheckStyle.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuCheckStyle_H_
#define	_MenuCheckStyle_H_

#include "MenuButtonSytle.h"

class nsMenuCheckStyle : public nsMenuButtonStyle
{
public:
	nsImageView				m_check;

public:
	static nsMenuCtrlStyle* Create() { return new nsMenuCheckStyle; }

protected:
	virtual bool			Parse( script_state_t *ss );
};

#endif	//_MenuCheckStyle_H_