// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuAds.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "MenuAds.h"

nsMenuAds::nsMenuAds( const char *id ) :
	nsMenuWnd( id ),
	m_flash( "ads.swf" )
{

}

//---------------------------------------------------------
// nsMenuAds::OnEvent:
//---------------------------------------------------------
bool nsMenuAds::OnEvent( const char *msg )
{
	if ( StrEqual( msg, "open" ) )
	{
		m_flash.Start( false, false, true );
		return true;
	}

	return false;
}

//---------------------------------------------------------
// nsMenuAds::Loop:
//---------------------------------------------------------
void nsMenuAds::Loop( float time )
{
	nsMenuWnd::Loop( time );

	if ( !m_flash.IsPlaying() )
	{
		Close();
		m_flash.Stop();
	}
}

