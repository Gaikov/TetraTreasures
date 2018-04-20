// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file RenPatchBuffer.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_RenPatchBuffer_H_
#define	_RenPatchBuffer_H_

#include "comm_types.h"
#include <pf/pftypes.h>

struct TLitVert;

class nsRenPatchBuffer
{
public:
	enum
	{
		IDX_PER_PATCH = 6,
		VERT_PER_PATCH = 4
	};

public:
	nsRenPatchBuffer( uint patchReserve );
	virtual ~nsRenPatchBuffer();

	void		ReallocBuffers( uint count );
	uint		GetMaxPatches() { return m_maxPatches; }

protected:
	uint16_t	*m_idx;
	TLitVert	*m_vert;

protected:
	void		DrawBuffer( uint patchCount );

private:
	uint		m_maxPatches;

private:
	void		FillIndices( uint startChar, uint maxChars );
};

#endif	//_RenPatchBuffer_H_