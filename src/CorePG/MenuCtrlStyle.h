// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuCtrlStyle.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuCtrlStyle_H_
#define	_MenuCtrlStyle_H_

#include "SmartPtr.h"
#include "Parser.h"
#include <pf/str.h>

class nsMenuCtrlStyle
{
friend class nsMenuMgr;

public:
	typedef nsSmartPtr<nsMenuCtrlStyle>	sp_t;

public:
	nsMenuCtrlStyle() {}
	virtual ~nsMenuCtrlStyle() {}

	const char*		GetClassID() { return m_classID.c_str(); }
	const char*		GetID() { return m_id.c_str(); }

	virtual bool	Parse( script_state_t *ss );

private:
	str				m_classID;
	str				m_id;
};

#endif	//_MenuCtrlStyle_H_