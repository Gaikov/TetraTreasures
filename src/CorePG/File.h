// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file File.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_File_H_
#define	_File_H_

#include "SmartPtr.h"
#include "comm_types.h"

class nsFile
{
public:
	typedef nsSmartPtr<nsFile>	sp_t;

public:
	static nsFile*	LoadFile( const char *fileName );

	nsFile();
	virtual ~nsFile();

	byte*			GetData() { return m_data; }
	uint			GetSize() { return m_size; }

protected:
	byte*	m_data;
	uint	m_size;
};

#endif	//_File_H_