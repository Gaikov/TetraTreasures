// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file ClassFactory.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_ClassFactory_H_
#define	_ClassFactory_H_

#include "Name.h"

template<class TBaseClass>
class nsClassFactory
{
public:
	typedef TBaseClass* (*CreateFunc)();

public:
	nsClassFactory() {}

	bool			ObjRegister( const char *classID, CreateFunc func );
	TBaseClass*		ObjCreate( const char *classID );
	TBaseClass*		ObjCreate( const nsName &name );

private:
	struct objDesc_t
	{
		nsName		classID;
		CreateFunc	func;
	};

	typedef std::vector<objDesc_t>	descList_t;

private:
	bool		m_valid;
	descList_t	m_descList;
};

//---------------------------------------------------------
// nsClassFactory::ObjRegister:
//---------------------------------------------------------
template<class TBaseClass>
bool nsClassFactory<TBaseClass>::ObjRegister( const char *classID, CreateFunc func )
{
	if ( !StrCheck( classID ) ) return false;

	objDesc_t	desc;
	desc.classID = nsName( classID );
	desc.func = func;
	m_descList.push_back( desc );
	return true;
}

//---------------------------------------------------------
// nsClassFactory::ObjCreate:
//---------------------------------------------------------
template<class TBaseClass>
typename TBaseClass* nsClassFactory<TBaseClass>::ObjCreate( const char *classID )
{
	if ( !StrCheck( classID ) ) return 0;
	descList_t::iterator	it;

	for ( it = m_descList.begin(); it != m_descList.end(); ++it )
	{
		objDesc_t	&desc = *it;
		if ( StrEqual( desc.classID.AsChar(), classID ) )
			return desc.func();
	}

	return 0;
}

//---------------------------------------------------------
// nsClassFactory::ObjCreate:
//---------------------------------------------------------
template<class TBaseClass>
typename TBaseClass* nsClassFactory<TBaseClass>::ObjCreate( const nsName &name )
{
	if ( !name.IsValid() ) return 0;
	descList_t::iterator	it;

	for ( it = m_descList.begin(); it != m_descList.end(); ++it )
	{
		objDesc_t	&desc = *it;
		if ( desc.classID == name )
			return desc.func();
	}

	return 0;
}

#endif	//_ClassFactory_H_