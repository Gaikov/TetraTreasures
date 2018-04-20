// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Name.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "Name.h"
#include "StrTools.h"

//---------------------------------------------------------
// nsName::nsName: 
//---------------------------------------------------------
nsName::nsName() :
	m_id( -1 )
{

}

//---------------------------------------------------------
// nsName::nsName: 
//---------------------------------------------------------
nsName::nsName( const char *name )
{
	m_id = nsNamePool::GetID( name );
}

//---------------------------------------------------------
// nsName::AsInt: 
//---------------------------------------------------------
int	nsName::AsInt() const
{
	return m_id;
}

//---------------------------------------------------------
// nsName::AsChar: 
//---------------------------------------------------------
const char*	nsName::AsChar() const
{
	return nsNamePool::GetNameByID( m_id );
}

//---------------------------------------------------------
// nsName::IsValid: 
//---------------------------------------------------------
bool nsName::IsValid() const
{
	return nsNamePool::IsValidID( m_id );
}

//---------------------------------------------------------
// nsName::operator ==: 
//---------------------------------------------------------
bool nsName::operator == ( const nsName &name ) const
{
	return m_id == name.m_id;
}

//---------------------------------------------------------
// nsName::operator !=: 
//---------------------------------------------------------
bool nsName::operator != ( const nsName &name ) const
{
	return m_id != name.m_id;
}

nsNamePool::nameList_t	nsNamePool::m_names;

//---------------------------------------------------------
// nsNamePool::GetID: 
//---------------------------------------------------------
int	nsNamePool::GetID( const char *name )
{
	if ( !name ) return -1;

	for ( int i = 0; i < (int)m_names.size(); ++i )
	{
		if ( StrEqual( m_names[i], name ) )
			return i;
	}

	m_names.push_back( strdup( name ) );
	return m_names.size() - 1;
}

//---------------------------------------------------------
// nsNamePool::GetNameByID: 
//---------------------------------------------------------
const char*	nsNamePool::GetNameByID( int id )
{
	if ( !IsValidID( id ) ) return "";
	return m_names[id];
}

//---------------------------------------------------------
// nsNamePool::IsValidID: 
//---------------------------------------------------------
bool nsNamePool::IsValidID( int id )
{
	return id >= 0 && id < (int)m_names.size();
}

//---------------------------------------------------------
// nsNamePool::Free: 
//---------------------------------------------------------
void nsNamePool::Free()
{
	for ( int i = 0; i < (int)m_names.size(); ++i )
		free( m_names[i] );
}
