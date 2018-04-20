// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file RenPatchBuffer.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "RenPatchBuffer.h"
#include <pf/renderer.h>
#include <pf/vertexset.h>

static uint16_t gs_patchIdx[nsRenPatchBuffer::IDX_PER_PATCH] = { 0, 1, 2, 0, 2, 3 };

//---------------------------------------------------------
// nsRenPatchBuffer::nsRenPatchBuffer:
//---------------------------------------------------------
nsRenPatchBuffer::nsRenPatchBuffer( uint patchReserve ) :
	m_idx( 0 ),
	m_vert( 0 ),
	m_maxPatches( 0 )
{
	ReallocBuffers( patchReserve );
}

//---------------------------------------------------------
// nsRenPatchBuffer::~nsRenPatchBuffer:
//---------------------------------------------------------
nsRenPatchBuffer::~nsRenPatchBuffer()
{
	if ( m_idx ) free( m_idx );
	if ( m_vert ) free( m_vert );
}

//---------------------------------------------------------
// nsRenPatchBuffer::ReallocBuffers:
//---------------------------------------------------------
void nsRenPatchBuffer::ReallocBuffers( uint count )
{
	if ( !count ) return;

	if ( !m_idx )
	{
		m_idx = (uint16_t*)malloc( sizeof(uint16_t) * IDX_PER_PATCH * count );
		m_maxPatches = count;
		FillIndices( 0, m_maxPatches );
	}
	else
	{
		m_idx = (uint16_t*)realloc( m_idx, sizeof(uint16_t) * IDX_PER_PATCH * count );
		if ( count > m_maxPatches ) FillIndices( m_maxPatches, count );
		m_maxPatches = count;
	}

	if ( !m_vert )
	{
		m_vert = (TLitVert*)malloc( sizeof(TLitVert) * VERT_PER_PATCH * count );
		m_maxPatches = count;
	}
	else
	{
		m_vert = (TLitVert*)realloc( m_vert, sizeof(TLitVert) * VERT_PER_PATCH * count );
		m_maxPatches = count;
	}
}

//---------------------------------------------------------
// nsRenPatchBuffer::DrawBuffer:
//---------------------------------------------------------
void nsRenPatchBuffer::DrawBuffer( uint patchCount )
{
	if ( patchCount > m_maxPatches )
	{
		assert( !"Invalid call" );
		return;
	}

	uint32_t	idxCount = IDX_PER_PATCH * patchCount;
	TVertexSet	vs( m_vert, VERT_PER_PATCH * patchCount );

	TRenderer::GetInstance()->DrawIndexedVertices( TRenderer::kDrawTriangles, vs, m_idx, idxCount );
}

//---------------------------------------------------------
// nsRenPatchBuffer::FillIndices:
//---------------------------------------------------------
void nsRenPatchBuffer::FillIndices( uint startChar, uint maxChars )
{
	for ( uint i = startChar; i < maxChars; ++i )
	{
		uint	startIdx = i * IDX_PER_PATCH;
		uint	startVert = i * VERT_PER_PATCH;
		for ( int j = 0; j < IDX_PER_PATCH; ++j )
			m_idx[startIdx + j] = gs_patchIdx[j] + startVert;
	}
}