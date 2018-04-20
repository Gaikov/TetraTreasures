// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FontManager.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FontManager_H_
#define	_FontManager_H_

#include "Font.h"
#include "FontRender.h"

class nsFontManager
{
public:
	static bool		Init();
	static void		Release();

	nsFont*			FontLoad( const char *fileName );
	void			FontRelease( nsFont *font );

	void			DrawTest();

	nsFontRender*	GetFontRender() { return &m_fntRen; }

private:
	bool			m_valid;

	nsFont			*m_list;
	nsFont			*m_testFont;

	nsFontRender	m_fntRen;

private:
	nsFont*			FontFind( const char *fileName );

	nsFontManager();
	~nsFontManager();
};

extern nsFontManager *g_fntMgr;

#endif	//_FontManager_H_