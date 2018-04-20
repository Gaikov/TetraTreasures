// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PartRender2.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_PartRender2_H_
#define	_PartRender2_H_

#include "RenPatchBuffer.h"
#include "Color.h"
#include "Vec2.h"

class nsPartRender2 : public nsRenPatchBuffer
{
public:
	nsPartRender2( uint partReserve );

	void	DrawBegin();
	void	AddParticle( const nsVec2 &pos, const nsVec2 &size, float angle, const nsColor &c );
	void	DrawFlush();

private:
	uint	m_partCount;
};

#endif	//_PartRender2_H_