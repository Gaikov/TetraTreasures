// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartManager.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "PartManager.h"
#include "time.h"

nsPartManager *g_partManager = 0;

//---------------------------------------------------------
// nsPartManager::nsPartManager:
//---------------------------------------------------------
nsPartManager::nsPartManager() :
	m_valid( true ),
	m_ren( 1000 )
{

}

//---------------------------------------------------------
// nsPartManager::~nsPartManager:
//---------------------------------------------------------
nsPartManager::~nsPartManager()
{

}

//---------------------------------------------------------
// nsPartManager::Init:
//---------------------------------------------------------
bool nsPartManager::Init()
{
	if ( !g_partManager )
	{
		g_partManager = new nsPartManager;
		if ( !g_partManager->m_valid )
		{
			delete g_partManager;
			g_partManager = 0;
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------
// nsPartManager::Release:
//---------------------------------------------------------
void nsPartManager::Release()
{
	if ( g_partManager )
	{
		delete g_partManager;
		g_partManager = 0;
	}
}

//---------------------------------------------------------
// nsPartManager::StateCreate:
//---------------------------------------------------------
nsPartState* nsPartManager::StateCreate( nsPartDesc *desc )
{
	if ( !desc ) return 0;
	
	nsPartState	*state = m_partCtrl.CreateState();
	if ( !state ) return 0;

	state->Init( desc );
	return state;
}

//---------------------------------------------------------
// nsPartManager::StateRemove:
//---------------------------------------------------------
void nsPartManager::StateRemove( nsPartState *state )
{
	if ( !state ) return;
	state->SetEmmit( false );
	m_partCtrl.FreeState( state );
}

//---------------------------------------------------------
// nsPartManager::MoveAll:
//---------------------------------------------------------
void nsPartManager::MoveAll()
{
	m_partCtrl.Move( g_frameTime );

	if ( m_partCtrl.StateFetchBegin() )
	{
		nsPartState*	s;
		while ( s = m_partCtrl.StateFetch() )
			s->Loop( g_frameTime );
	}
}

//---------------------------------------------------------
// nsPartManager::DrawAll:
//---------------------------------------------------------
void nsPartManager::DrawAll()
{
	if ( m_partCtrl.StateFetchBegin() )
	{
		nsPartState*	s;
		while ( s = m_partCtrl.StateFetch() )
		{
			if ( !s->m_selfDraw )
				s->DrawParticles();
		}
	}
}