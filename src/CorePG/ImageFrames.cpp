// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file ImageFrames.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "ImageFrames.h"
#include "StrTools.h"

//---------------------------------------------------------
// nsImageFrames::nsImageFrames:
//---------------------------------------------------------
nsImageFrames::nsImageFrames()
{

}

//---------------------------------------------------------
// nsImageFrames::~nsImageFrames:
//---------------------------------------------------------
nsImageFrames::~nsImageFrames()
{
	for ( int i = 0; i < (int)m_imgList.size(); ++i )
		delete m_imgList[i];
}

//---------------------------------------------------------
// nsImageFrames::Parse:
//---------------------------------------------------------
bool nsImageFrames::Parse( script_state_t *ss )
{
	
	return true;
}

//---------------------------------------------------------
// nsImageFrames::Append:
//---------------------------------------------------------
bool nsImageFrames::Append( const char *fileName, const nsVec2 &frameSize, const uint gridSize[2] )
{
	if ( !StrCheck( fileName ) ) return false;

	nsVec2	texPos( 0, 0 );
	for ( uint y = 0; y < gridSize[1]; ++y )
	{
		texPos.x = 0;
		for ( uint x = 0; x < gridSize[0]; ++x )
		{
			nsImageView	*img = new nsImageView( fileName, texPos, frameSize );
			m_imgList.push_back( img );
			
			texPos.x += frameSize.x;
		}

		texPos.y += frameSize.y;
	}

	return true;
}

//---------------------------------------------------------
// nsImageFrames::DrawFrame:
//---------------------------------------------------------
void nsImageFrames::DrawFrame( uint frame, const nsVec2 &pos, const nsVec2 &size, float angle /*= 0*/, const nsColor &c /*= nsColor( 1, 1, 1, 1 )*/, uint align /*= 0 */ ) const
{
	if ( frame >= m_imgList.size() ) return;
	m_imgList[frame]->Draw( pos, size, angle, c, align );
}

//---------------------------------------------------------
// nsImageFrames::GetCount:
//---------------------------------------------------------
int nsImageFrames::GetCount()
{
	return m_imgList.size();
}
