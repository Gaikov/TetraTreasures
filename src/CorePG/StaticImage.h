// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file StaticImage.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_StaticImage_H_
#define	_StaticImage_H_

#include "ImageView.h"
#include "SmartPtr.h"

class nsStaticImage
{
public:
	typedef nsSmartPtr<nsStaticImage>			sp_t;

public:
	bool		Parse( script_state_t *ss );
	void		Draw();
	
private:
	nsImageView	m_img;

	nsVec2		m_pos;
	nsVec2		m_size;
	nsColor		m_color;
};

#endif	//_StaticImage_H_