// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file State.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "State.h"

//---------------------------------------------------------
// nsState::nsState:
//---------------------------------------------------------
nsState::nsState() :
	m_active( 0 ),
	m_currState( 0 ),
	m_callback( 0 )
{

}

//---------------------------------------------------------
// nsState::AddState:
//---------------------------------------------------------
void nsState::AddState( int id, float time )
{
	state_t	s = { id, time };
	m_list.push_back( s );
}

//---------------------------------------------------------
// nsState::StartState:
//---------------------------------------------------------
void nsState::StartState( int id )
{
	state_t	*curr = m_active;
	
	for ( int i = 0; i < (int)m_list.size(); ++i )
	{
		state_t	*s = &m_list[i];
		if ( s->id == id )
		{
			m_active = s;
			m_active->currTime = m_active->maxTime;
			m_currState = i;
			if ( m_callback )
				m_callback->OnStateChange( curr, m_active );
			return;
		}
	}
}

//---------------------------------------------------------
// nsState::Start:
//---------------------------------------------------------
void nsState::Start()
{
	if ( !m_list.size() ) return;
	m_active = &m_list[0];
	m_currState = 0;
	m_active->currTime = m_active->maxTime;

	if ( m_callback )
		m_callback->OnStateChange( 0, m_active );
}

//---------------------------------------------------------
// nsState::Loop:
//---------------------------------------------------------
void nsState::Loop( float time )
{
	if ( !m_active || !m_active->maxTime ) return;

	m_active->currTime -= time;
	if ( m_active->currTime <= 0 )
	{
		state_t	*curr = m_active;
		m_active = 0;
		m_currState ++;
		if ( m_currState < (int)m_list.size() )
		{
			m_active = &m_list[m_currState];
			m_active->currTime = m_active->maxTime;
		}

		if ( m_callback )
			m_callback->OnStateChange( curr, m_active );
	}
}

//---------------------------------------------------------
// nsState::GetCurrState:
//---------------------------------------------------------
const state_t* nsState::GetCurrState()
{
	return m_active;
}