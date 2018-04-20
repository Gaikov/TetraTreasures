// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Var.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Var_H_
#define	_Var_H_

#include "comm_types.h"

class nsVar
{
public:
	nsVar();
	~nsVar();

	float		Value() { return 0; }
	const char*	String() { return ""; }
protected:
	
private:
};

#endif	//_Var_H_