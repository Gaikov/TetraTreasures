// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file ImageFrames.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_ImageFrames_H_
#define	_ImageFrames_H_

#include "headers.h"
#include "ImageView.h"

class nsImageFrames
{
public:
	nsImageFrames();
	virtual ~nsImageFrames();

	bool			Parse( script_state_t *ss );
	bool			Append( const char *fileName, const nsVec2 &frameSize, const uint gridSize[2] );

	void			DrawFrame( uint frame, const nsVec2 &pos, const nsVec2 &size, float angle = 0, const nsColor &c = nsColor( 1, 1, 1, 1 ), uint align = 0 ) const;
	int				GetCount();

private:
	typedef std::vector<nsImageView*>	imgList_t;

private:
	imgList_t		m_imgList;
};



#endif	//_ImageFrames_H_