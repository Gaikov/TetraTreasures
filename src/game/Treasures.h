// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Treasures.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Treasures_H_
#define	_Treasures_H_

#include "common.h"
#include "CorePG/Singl.h"
#include "CorePG/PartSimple.h"

class nsTreasures : public nsSingl<nsTreasures>
{
public:
	nsTreasures();
	~nsTreasures();

	void	NewGame();
	bool	IsActive() { return m_parts.IsActive(); }

	void	SetCompo( int mul );
	
	void	BreakStart( float velStart, float velStep );
	void	BreakBox( int cellX, int cellY, int type );
	
	void	OnMouseMove( const nsVec2 &mouse );
	void	Loop();
	void	Draw();

private:
	struct bowlParams
	{
		nsVec2	pos;
		float	halfSize;
	};

	struct part_t
	{
		int			type;
		nsVec2		pos;
		nsVec2		vel;
		bool		dead;
		nsPartState	*ps;
	};

	struct nsPartMove
	{
		bool operator () ( part_t *p, float time, void* )
		{
			return !p->dead;
		}
	};

	struct partPoints_t
	{
		nsVec2	pos;
		float	life;
		int		points;
	};

	struct nsPointsMove
	{
		bool operator () ( partPoints_t *p, float time, void* )
		{
			p->pos.y -= time * 100.0f;
			p->life -= time;// * 0.5f;
			if ( p->life <= 0 )
				return false;
			return true;
		}
	};

private:
	nsPartSimple<part_t, nsPartMove, 100>			m_parts;
	nsPartDesc										m_partDesc;

	nsPartSimple<partPoints_t, nsPointsMove, 100>	m_points;
	nsFont			*m_fontPoints;
	nsImageView		m_imgPoints;

	nsImageView		m_bowl;
	bowlParams		m_bowlParams;
	nsPartDesc		m_partCatch;
	int				m_mul;
	TSoundRef		m_sndCatch;

	float			m_velCurr;
	float			m_velStep;
	float			m_velStart;

	bool			m_combo;
	nsFont			*m_fontCombo;
	float			m_comboTime;
	nsString		m_comboText;
	TSoundRef		m_comboSnd;
};

extern nsTreasures	*g_tres;

#endif //_Treasures_H_