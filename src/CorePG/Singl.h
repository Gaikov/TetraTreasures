// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Singl.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Singl_H_
#define	_Singl_H_

template <class T>
class nsSingl
{
public:
	static bool Init();
	static void Release();

	inline T*	GetInst() { return m_inst; }

protected:
	bool		m_valid;
	static T	*m_inst;

protected:
	nsSingl();
	virtual ~nsSingl() {}
};

template <class T>
typename T *nsSingl<T>::m_inst = 0;

//---------------------------------------------------------
// nsSingl<T>::nsSingl:
//---------------------------------------------------------
template <class T>
nsSingl<T>::nsSingl() :
	m_valid( false )
{

}

//---------------------------------------------------------
// nsSingl<T>::Init:
//---------------------------------------------------------
template <class T>
bool nsSingl<T>::Init()
{
	if ( !m_inst )
	{
		m_inst = new T;
		if ( !m_inst->m_valid )
		{
			delete m_inst;
			return false;
		}
	}
	return true;
}

//---------------------------------------------------------
// nsSingl<T>::Release:
//---------------------------------------------------------
template <class T>
void nsSingl<T>::Release()
{
	if ( m_inst )
	{
		delete m_inst;
		m_inst = 0;
	}
}

#endif	//_Singl_H_