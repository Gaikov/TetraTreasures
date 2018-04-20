// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartTpl.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_PartTpl_H_
#define	_PartTpl_H_

#include "EasyList.h"
#include <assert.h>

template <class TPart, class TMoveFunc, class TPartState, int TMaxParts, int TMaxStates>
class nsPartTpl
{
public:
	nsPartTpl() :
		m_partsFree( 0 ),
		m_stateActive( 0 ),
		m_stateFetch( 0 )
	{
		FreeAll();
	};

	//---------------------------------------------------------
	// CreateState:
	//---------------------------------------------------------
	inline TPartState*	CreateState()
	{
		if ( !m_stateFree ) return 0;

		_partState	*state = m_stateFree;
		DelFromList( &m_stateFree, state );
		AddToList( &m_stateActive, state );
		state->m_active = 0;
		state->m_fetch = 0;
		state->m_remove = false;
		return state;
	}

	//---------------------------------------------------------
	// FreeState:
	//---------------------------------------------------------
	inline void FreeState( TPartState *s )
	{
		_partState	*state = (_partState*)s;
		if ( state->m_remove )
		{
			assert( !"already removing" );
			return;
		}
		state->m_remove = true;
	}

	//---------------------------------------------------------
	// CreatePart:
	//---------------------------------------------------------
	inline TPart*	CreatePart( TPartState *s )
	{
		if ( !m_partsFree ) return 0;
		_partState	*state = (_partState*)s;
		if ( state->m_remove )
		{
			assert( !"removing state" );
			return 0;
		}

		_part	*part = m_partsFree;
		DelFromList( &m_partsFree, part );
		AddToList( &state->m_active, part );
		return part;
	}

	//---------------------------------------------------------
	// Move:
	//---------------------------------------------------------
	void	Move( float time )
	{
		_partState	*state = m_stateActive;
		_partState	*stNext = 0;
		while ( state )
		{
			_part	*next = 0;
			_part	*part = state->m_active;
			while ( part )
			{
				if ( !m_moveFunc( part, time ) )
				{
					next = part->next;
					DelFromList( &state->m_active, part );
					AddToList( &m_partsFree, part );
					part = next;
				}
				else
					part = part->next;
			}

			if ( state->m_remove && !state->m_active )
			{
				stNext = state->next;
				DelFromList( &m_stateActive, state );
				AddToList( &m_stateFree, state );
				state = stNext;
			}
			else
				state = state->next;
		}
	}

	//---------------------------------------------------------
	// FreeAll:
	//---------------------------------------------------------
	void	FreeAll()
	{
		m_stateFree = 0;
		m_stateActive = 0;
		m_stateFetch = 0;
		m_stateQueue = 0;

		for ( int i = 0; i < TMaxParts; ++i )
			AddToList( &m_partsFree, &m_partStore[i] );

		for ( int i = 0; i < TMaxStates; ++i )
		{
			m_stateStore[i].m_remove = true;
			AddToList( &m_stateFree, &m_stateStore[i] );
		}
	}

	//---------------------------------------------------------
	// FetchBegin:
	//---------------------------------------------------------
	bool	FetchBegin( TPartState *s ) const
	{
		_partState	*state = (_partState*)s;
		m_stateFetch = state;
		state->m_fetch = state->m_active;
		return state->m_fetch != 0;
	}

	//---------------------------------------------------------
	// Fetch:
	//---------------------------------------------------------
	inline TPart*	Fetch() const
	{
		if ( !m_stateFetch || !m_stateFetch->m_fetch ) return 0;

		_part	*part = m_stateFetch->m_fetch;
		m_stateFetch->m_fetch = part->next;
		return part;
	};

	//---------------------------------------------------------
	// StateFetchBegin:
	//---------------------------------------------------------
	bool StateFetchBegin() const
	{
		m_stateQueue = m_stateActive;
		return m_stateQueue != 0;
	}

	//---------------------------------------------------------
	// StateFetch:
	//---------------------------------------------------------
	inline TPartState* StateFetch() const
	{
		if ( !m_stateQueue ) return 0;
		TPartState *s = m_stateQueue;
		m_stateQueue = m_stateQueue->next;
		return s;
	};

private:
	struct _part : public TPart
	{
		_part		*prev, *next;
	};

	struct _partState : public TPartState
	{
		_partState	*prev, *next;
		_part		*m_active;
		_part		*m_fetch;
		bool		m_remove;	//удалить не удаляя частиц
	};

private:
	_part				m_partStore[TMaxParts];
	_part				*m_partsFree;

	_partState			m_stateStore[TMaxStates];
	_partState			*m_stateFree;
	_partState			*m_stateActive;
	mutable _partState	*m_stateFetch;	//для выборки партиклов
	mutable _partState	*m_stateQueue;	//для выборки стейтов

	TMoveFunc			m_moveFunc;
};

#endif	//_PartTpl_H_