// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Sound.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "Sound.h"

#define SOUND_GROUP	1
#define MUSIC_GROUP 2

//---------------------------------------------------------
// Sound_Load:
//---------------------------------------------------------
TSoundRef Sound_Load( const char *fileName )
{
	return TSound::Get( fileName, true, SOUND_GROUP );
}

//---------------------------------------------------------
// Sound_Play:
//---------------------------------------------------------
TSoundInstanceRef Sound_Play( TSoundRef snd, bool loop /*= false */ )
{
	if ( snd )
		return snd->Play( loop );
	return TSoundInstanceRef();
}

//---------------------------------------------------------
// Music_Load:
//---------------------------------------------------------
TSoundRef Music_Load( const char *fileName )
{
	return TSound::Get( fileName, false, MUSIC_GROUP );
}
