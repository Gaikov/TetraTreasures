// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file common.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_common_H_
#define	_common_H_

#include <pf/platform.h>
#include <pf/random.h>
#include <pf/sound.h>
#include <pf/simplehttp.h>

#include "CorePG/AppInfo.h"
#include "CorePG/Core.h"
#include "CorePG/MenuMgr.h"
#include "CorePG/RenAux.h"
#include "CorePG/StrTools.h"
#include "CorePG/PartRender2.h"
#include "CorePG/EasyList.h"
#include "CorePG/time.h"
#include "CorePG/LocalMgr.h"
#include "CorePG/Str.h"
#include "CorePG/PartManager.h"
#include "CorePG/ParseFile.h"
#include "CorePG/FontManager.h"
#include "CorePG/Sound.h"

struct nsGameStat
{
	int		m_score;
	float	m_time;
};

extern nsGameStat	g_gameStat;

#ifdef _DEBUG
#define ONLINE_LINK "http://localhost/free-casual-game/ttreasures.php#scores"
#else
#define ONLINE_LINK "http://free-casual-game.com/ttreasures.php#scores"
#endif

#endif	//_common_H_