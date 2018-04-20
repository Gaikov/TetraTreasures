// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuScore.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuScore_H_
#define	_MenuScore_H_

#include "common.h"

class nsMenuScore : public nsMenuWnd
{
public:
	nsMenuScore( const char *id );


	virtual bool	OnEvent( const char *msg );
	virtual bool	OnCtrlEvent( nsMenuControl *ctrl, const char *msg );
	void			UpdateTime();
	void			UpdateScore();
	bool			SumbitScore();

	const char*		GetUserName();
};

#endif //_MenuScore_H_