// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuMsg.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuMsg_H_
#define	_MenuMsg_H_

#include "common.h"

class nsMenuMsg : public nsMenuWnd
{
public:
	nsMenuMsg( const char *id );

	static void		ShowMsg( const char *caption, const char *msg );

	void			SetCaption( const char *caption );
	void			SetMessage( const char *msg );

private:
	virtual bool	OnCtrlEvent( nsMenuControl *ctrl, const char *msg );

};



#endif //_MenuMsg_H_