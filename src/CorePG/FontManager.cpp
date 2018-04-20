// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FontManager.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "FontManager.h"
#include "color.h"
#include "Config.h"
#include "log.h"
#include "StrTools.h"
#include "EasyList.h"

nsFontManager	*g_fntMgr = 0;

nsVar			*ft_file = 0;
nsVar			*ft_str = 0;
nsVar			*ft_pos_x = 0;
nsVar			*ft_pos_y = 0;
nsVar			*ft_enable = 0;

//---------------------------------------------------------
// nsFontManager::nsFontManager:
//---------------------------------------------------------
nsFontManager::nsFontManager() :
	m_valid( true ),
	m_list( 0 ),
	m_testFont( 0 ),
	m_fntRen( 100 )
{
	ft_enable = g_cfg->RegVar( "ft_enable", "0", 0 );
	ft_file = g_cfg->RegVar( "ft_file", "", GVF_SAVABLE );
	ft_str = g_cfg->RegVar( "ft_str", "", GVF_SAVABLE );
	ft_pos_x = g_cfg->RegVar( "ft_pos_x", "100", GVF_SAVABLE );
	ft_pos_y = g_cfg->RegVar( "ft_pos_y", "100", GVF_SAVABLE );
}

//---------------------------------------------------------
// nsFontManager::~nsFontManager:
//---------------------------------------------------------
nsFontManager::~nsFontManager()
{
	LogPrintf( PRN_ALL, "...clear fonts\n" );

	while ( m_list )
	{
		nsFont	*del = m_list;
		m_list = m_list->next;
		delete del;
	}
}

//---------------------------------------------------------
// nsFontManager::Init:
//---------------------------------------------------------
bool nsFontManager::Init()
{
	if ( !g_fntMgr )
	{
		g_fntMgr = new nsFontManager;
		if ( !g_fntMgr->m_valid )
		{
			delete g_fntMgr;
			g_fntMgr = 0;
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------
// nsFontManager::Release:
//---------------------------------------------------------
void nsFontManager::Release()
{
	if ( g_fntMgr )
	{
		delete g_fntMgr;
		g_fntMgr = 0;
	}
}

//---------------------------------------------------------
// nsFontManager::FontLoad:
//---------------------------------------------------------
nsFont*	nsFontManager::FontLoad( const char *fileName )
{
	if ( !StrCheck( fileName ) ) return 0;

	nsFont	*f = FontFind( fileName );
	if ( f ) return f;

	f = new nsFont;
	if ( !f->Load( fileName ) )
	{
		delete f;
		return 0;
	}

	AddToList( &m_list, f );
	return f;
}

//---------------------------------------------------------
// nsFontManager::FontRelease:
//---------------------------------------------------------
void nsFontManager::FontRelease( nsFont *font )
{
	if ( !font ) return;

	font->m_refCount --;
	if ( font->m_refCount <= 0 )
	{
		DelFromList( &m_list, font );
		delete font;
	}
}

//---------------------------------------------------------
// nsFontManager::DrawTest:
//---------------------------------------------------------
void nsFontManager::DrawTest()
{
	if ( !ft_enable->Value() ) return;

	if ( strlen( ft_file->String() ) 
		&& (!m_testFont || m_testFont->m_fileName != ft_file->String()) )
	{
		if ( m_testFont ) FontRelease( m_testFont );
		m_testFont = FontLoad( ft_file->String() );
		if ( !m_testFont ) return;
	}

	float	pos[2] = { ft_pos_x->Value(), ft_pos_y->Value() };

	float	s[2] = { 1, 1 };
	m_testFont->Draw( ft_str->String(), pos, s, nsColor::white, 0 );
}

//---------------------------------------------------------
// nsFontManager::FontFind:
//---------------------------------------------------------
nsFont*	nsFontManager::FontFind( const char *fileName )
{
	nsString	name = fileName;
	name.ConvFileName();
	
	for ( nsFont *f = m_list; f; f = f->next )
	{
		if ( f->m_fileName == name )
			return f;
	}

	return 0;
}
