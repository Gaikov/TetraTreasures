// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Sound.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Sound_H_
#define	_Sound_H_

#include <pf/sound.h>

TSoundRef			Sound_Load( const char *fileName );
TSoundInstanceRef	Sound_Play( TSoundRef snd, bool loop = false );

TSoundRef			Music_Load( const char *fileName );

#endif //_Sound_H_