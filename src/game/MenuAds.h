// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuAds.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuAds_H_
#define	_MenuAds_H_

#include "common.h"
#include <pf/flashhost.h>

class nsMenuAds : public nsMenuWnd
{
public:
	nsMenuAds( const char *id );

	virtual bool	OnEvent( const char *msg );
	virtual void	Loop( float time );

private:
	TFlashHost		m_flash;
};

#endif //_MenuAds_H_