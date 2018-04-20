// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuMain.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuMain_H_
#define	_MenuMain_H_

#include "common.h"
#include <CorePG/PartSimple.h>
#include <CorePG/Spline2.h>

class nsMenuMain : public nsMenuWnd
{
public:
	nsMenuMain( const char *id );

	virtual bool	OnCtrlEvent( nsMenuControl *ctrl, const char *msg );
	virtual void	Loop( float time );
	virtual void	Draw();

private:
	struct part_t
	{
		int			type;
		nsVec2		pos;
		nsVec2		nextPos;
		nsVec2		nextVel;
		float		time;
		float		maxTime;
		nsSpline2	sp;
		nsPartState	*ps;
	};

	struct partMove
	{
		bool operator () ( part_t *p, float time, void* )
		{
			p->time += time;
			if ( p->time >= p->maxTime )
			{
				nsVec2	pos;
				pos.x = Math_Rand( 640 );
				pos.y = Math_Rand( 480 );
				nsVec2	vel;
				vel.x = Math_Rand( 200 );
				vel.y = Math_Rand( 200 );
				vel.Norm();
				vel *= 200;

				float	dist = (pos - p->nextPos).Length();
				p->time -= p->maxTime;
				p->maxTime = dist / 200.0f;
				
				p->sp.SetSegment( p->nextPos, p->nextVel, pos, vel, p->maxTime );
				p->nextPos = pos;
				p->nextVel = vel;
			}

			p->sp.CalcPos( p->time, p->pos );
			p->ps->SetPos( p->pos );
			return true;
		}
	};

private:
	drawSprite_t					m_sprBack;
	nsVec2							m_backSize;
	float							m_backOffs;
	float							m_backAngle;

	nsPartSimple<part_t, partMove, 20>	m_parts;
	nsPartDesc						m_partBack;
};

#endif //_MenuMain_H_