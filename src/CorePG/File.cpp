// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file File.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "File.h"
#include <pf/file.h>

//---------------------------------------------------------
// nsFile::nsFile:
//---------------------------------------------------------
nsFile::nsFile() :
	m_data( 0 ),
	m_size( 0 )
{

}

//---------------------------------------------------------
// nsFile::~nsFile:
//---------------------------------------------------------
nsFile::~nsFile()
{
	if ( m_data ) delete [] m_data;
}

//---------------------------------------------------------
// nsFile::LoadFile:
//---------------------------------------------------------
nsFile* nsFile::LoadFile( const char *fileName )
{
	TFile	file;
	if ( !file.Open( fileName, kReadBinary ) ) return 0;

	nsFile	*res = new nsFile;

	file.Seek( 0, kSeekEnd );
	res->m_size = file.Tell();
	file.Seek( 0, kSeekStart );

	res->m_data = new byte[res->m_size + 1];
	if ( file.Read( res->m_data, res->m_size ) != res->m_size )
	{
		delete res;
		return 0;
	}

	res->m_data[res->m_size] = 0;
	return res;
}
