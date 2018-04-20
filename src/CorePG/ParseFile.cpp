// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file ParseFile.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "ParseFile.h"
#include "StrTools.h"
#include "log.h"

//---------------------------------------------------------
// nsParseFile::nsParseFile: 
//---------------------------------------------------------
nsParseFile::nsParseFile()
{
	
}

//---------------------------------------------------------
// nsParseFile::~nsParseFile: 
//---------------------------------------------------------
nsParseFile::~nsParseFile()
{
	for ( int i = 0; i < (int)m_files.size(); ++i )
	{
		if ( m_files[i].ss )
			ps_end( m_files[i].ss );
	}
}

//---------------------------------------------------------
// nsParseFile::BeginFile: 
//---------------------------------------------------------
script_state_t* nsParseFile::BeginFile( const char *fileName, char prefix )
{
	if ( !StrCheck( fileName ) ) return 0;

	scriptFile_t	script;

	script.file = nsFile::LoadFile( fileName );
	if ( !script.file ) return 0;
	
	script.ss = ps_begin( (char*)script.file->GetData(), prefix );

	m_files.push_back( script );
	return script.ss;
}
