// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file State.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_State_H_
#define	_State_H_

#include <vector>

//---------------------------------------------------------
// state_t:
//---------------------------------------------------------
struct state_t
{
	int		id;
	float	maxTime;
	float	currTime;
};

//---------------------------------------------------------
// IStateCallback:
//---------------------------------------------------------
struct IStateCallback
{
	virtual void OnStateChange( const state_t *curr, const state_t *next ) = 0;
};

//---------------------------------------------------------
// nsState:
//---------------------------------------------------------
class nsState
{
public:
	nsState();
	void			AddState( int id, float time );
	void			StartState( int id );
	void			Start();
	void			Loop( float time );
	const state_t*	GetCurrState();
	void			SetCallback( IStateCallback *cb ) { m_callback = cb; }

private:
	typedef std::vector<state_t>	stateList_t;

private:
	stateList_t		m_list;
	state_t			*m_active;
	int				m_currState;
	IStateCallback	*m_callback;
};

#endif	//_State_H_