// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartSimple.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_PartSimple_H_
#define	_PartSimple_H_

template <class TPart, class TMoveFunc, int TMaxParts, class TData = void>
class nsPartSimple
{
public:
	nsPartSimple() :
		m_active( 0 ),
		m_free( 0 ),
		m_data( 0 )
	{
		FreeAll();
	};

	//---------------------------------------------------------
	// IsActive:
	//---------------------------------------------------------
	inline bool IsActive()
	{
		return m_active != 0;
	}

	//---------------------------------------------------------
	// CreatePart:
	//---------------------------------------------------------
	inline TPart*	CreatePart()
	{
		if ( !m_free ) return 0;
		
		nsPart	*part = m_free;
		DelFromList( &m_free, part );
		AddToList( &m_active, part );
		return part;
	}
	
	//---------------------------------------------------------
	// Move:
	//---------------------------------------------------------
	void	Move( float time )
	{
		nsPart	*next = 0;
		nsPart	*part = m_active;
		while ( part )
		{
			if ( !m_moveFunc( part, time, m_data ) )
			{
				next = part->next;
				DelFromList( &m_active, part );
				AddToList( &m_free, part );
				part = next;
			}
			else
				part = part->next;
		}
	}
	
	//---------------------------------------------------------
	// FreeAll:
	//---------------------------------------------------------
	void	FreeAll()
	{
		m_active = 0;

		for ( int i = 0; i < TMaxParts; ++i )
			AddToList( &m_free, &m_partSore[i] );
	}

	//---------------------------------------------------------
	// FetchBegin:
	//---------------------------------------------------------
	bool	FetchBegin() const
	{
		m_fetch = m_active;
		return m_fetch != 0;
	}

	//---------------------------------------------------------
	// Fetch:
	//---------------------------------------------------------
	inline TPart*	Fetch() const
	{
		if ( !m_fetch ) return 0;

		nsPart	*part = m_fetch;
		m_fetch = part->next;
		return part;
	};

	inline void		SetData( TData *data )
	{
		m_data = data;
	}

private:
	struct nsPart : public TPart
	{
		nsPart	*prev, *next;
	};

private:
	nsPart				m_partSore[TMaxParts];
	nsPart				*m_active;
	nsPart				*m_free;
	mutable nsPart		*m_fetch;

	TMoveFunc			m_moveFunc;
	TData				*m_data;
};

#endif	//_PartSimple_H_