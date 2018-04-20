// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuButtonSytle.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuButtonSytle_H_
#define	_MenuButtonSytle_H_

#include "MenuCtrlStyle.h"
#include "ImageView.h"
#include "Font.h"
#include <pf/sound.h>

class nsMenuButtonStyle : public nsMenuCtrlStyle
{
public:
	nsImageView	m_up, m_down, m_over;
	nsFont		*m_font;
	nsColor		m_textColor;
	nsVec2		m_textScale;

	TSoundRef	m_sndDown;
	TSoundRef	m_sndOver;

public:
	static nsMenuCtrlStyle*	Create() { return new nsMenuButtonStyle; }

protected:
	nsMenuButtonStyle();
	
	virtual bool Parse( script_state_t *ss );
};

#endif	//_MenuButtonSytle_H_