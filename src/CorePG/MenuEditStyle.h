// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuEditStyle.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuEditStyle_H_
#define	_MenuEditStyle_H_

#include "MenuCtrlStyle.h"
#include "ImageView.h"
#include "Font.h"
#include <pf/sound.h>

class nsMenuEditStyle : public nsMenuCtrlStyle
{
public:
	nsFont			*m_font;
	nsColor			m_textColor;
	nsVec2			m_textScale;

	nsImageView		m_up;
	nsImageView		m_over;

	TSoundRef		m_sndOver;

public:
	static nsMenuCtrlStyle*	Create() { return new nsMenuEditStyle; }

protected:
	nsMenuEditStyle();
	virtual bool			Parse( script_state_t *ss );
};

#endif	//_MenuEditStyle_H_