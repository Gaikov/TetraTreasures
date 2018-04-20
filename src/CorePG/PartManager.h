// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartManager.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_PartManager_H_
#define	_PartManager_H_

#include "PartTpl.h"
#include "PartState.h"
#include "PartDesc.h"
#include "PartRender2.h"

//---------------------------------------------------------
// particle_t:
//---------------------------------------------------------
struct particle_t
{
	nsVec2	pos;
	nsVec2	vel;
	float	grav;
	float	scale;
	float	angle;
	float	angleRot;
	float	life;
	float	lifeVel;
};

//---------------------------------------------------------
// nsPartManager:
//---------------------------------------------------------
class nsPartManager
{
friend class nsPartState;

public:
	static bool		Init();
	static void		Release();

	nsPartState*	StateCreate( nsPartDesc *desc );
	void			StateRemove( nsPartState *state );

	void			MoveAll();
	void			DrawAll();

private:
	struct nsPartMove
	{
		inline bool operator () ( particle_t *p, float time )
		{
			p->life -= p->lifeVel * time;
			if ( p->life <= 0 ) return false;

			p->vel.y += p->grav * time;
			p->pos += p->vel * time;

			p->angle += p->angleRot * time;

			return true;
		}
	};

	typedef nsPartTpl<particle_t, nsPartMove, nsPartState, 10000, 1000>	partCtrl_t;

private:
	bool			m_valid;
	partCtrl_t		m_partCtrl;
	nsPartRender2	m_ren;

private:
	nsPartManager();
	~nsPartManager();
};

extern nsPartManager *g_partManager;

#endif	//_PartManager_H_