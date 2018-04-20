// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file MenuFrame.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_MenuFrame_H_
#define	_MenuFrame_H_

#include "headers.h"
#include "SmartPtr.h"
#include "Parser.h"
#include <pf/vertexset.h>
#include <pf/texture.h>

class nsMenuFrame
{
public:
	typedef nsSmartPtr<nsMenuFrame>	sp_t;

	bool	Parse( script_state_t *ss );
	void	Draw();

private:
	typedef std::vector<TLitVert>	vertList_t;
	typedef std::vector<uint16_t>	idxList_t;

private:
	TTextureRef	m_tex;
	vertList_t	m_vert;
	idxList_t	m_idx;

private:
	void	AddQuad( TLitVert v[4] );
	float	TexCoord( int idx );
	int		TexIdx( int cell, int size );
};

#endif //_MenuFrame_H_