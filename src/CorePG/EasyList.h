// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file EasyList.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_EasyList_H_
#define	_EasyList_H_

//-----------------------------------------------------
//  AddToList:  
//-----------------------------------------------------
template <class T>
inline void AddToList( T** lst, T* data )
{
	data->prev = 0;
	if ( *lst ) (*lst)->prev = data;
	data->next = *lst;
	(*lst) = data;
}


//-----------------------------------------------------
//  DelFromList:  
//-----------------------------------------------------
template <class T>
inline void DelFromList( T** lst, T* data )
{
	if ( *lst == data ) *lst = data->next;
	T* prev = data->prev;
	T* next = data->next;
	if ( prev ) prev->next = next;
	if ( next ) next->prev = prev;
}

#endif	//_EasyList_H_