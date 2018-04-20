// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Font.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Font_H_
#define	_Font_H_

#include "FontRender.h"
#include "SmartPtr.h"
#include "Str.h"
#include <pf/texture.h>

#define	MAX_CHARS	256

class IFontCallback
{
public:
	virtual void OnChar( int num, charDrawParams_t &dp ) = 0;
};

//---------------------------------------------------------
// nsFont: 
//---------------------------------------------------------
class nsFont  
{
friend class nsFontManager;

public:
	typedef nsSmartPtr<nsFont>	sp_t;

public:
	nsFont		*prev, *next;

public:
	nsFont();
	~nsFont();

	static nsFont::sp_t Create( const char *fileName );

	void				Draw( const char *str, const nsVec2 &pos, const nsVec2 &scale = nsVec2( 1, 1 ), const nsColor &c = nsColor::white, int len = 0 );
	void				DrawFX( const char *str, const nsVec2 &pos, const nsVec2 &scale, const nsColor &c, int len, IFontCallback *fcb );
	void				GetSize( const char *str, nsVec2 &size, int len = 0 );
	float				GetBase() { return m_baseLine; }
	const charView_t*	GetCharView( uchar ch );

private:
	typedef std::vector<TTextureRef>	texList_t;

private:
	struct charDesc_t 
	{
		TTextureRef	tex;
		charView_t	v;
	};

	nsString	m_fileName;
	int			m_refCount;

	texList_t	m_texList;
	
	float		avg_height;		//максимальна€ высота символа (верхн€€ граница - нижн€€)
	float		m_baseLine;		//ќт базовой линии до нижней границы
	charDesc_t	ch[MAX_CHARS];

private:
	bool		Load( const char *filename );
};

void Font_DrawAligned( nsFont *font, const char *str, const nsVec2 &pos, uint align, const nsVec2 &scale = nsVec2( 1, 1 ), const nsColor &c = nsColor::white, int len = 0 );

#endif //_Font_H_