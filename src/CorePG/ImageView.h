// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file ImageView.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_ImageView_H_
#define	_ImageView_H_

#include "comm_types.h"
#include "Vec2.h"
#include "Color.h"
#include "Parser.h"
#include "RenAux.h"
#include "Align.h"

class nsImageView
{
public:
	nsImageView() {}
	nsImageView( const char *fileName, const nsVec2 &texPos, const nsVec2 &texSize );
	virtual					~nsImageView();
	bool					Parse( script_state_t *ss, const char *blockName );
	bool					Parse( script_state_t *ss );
	const nsVec2&			GetSize() const { return m_texSize; }

	void					Draw( const nsVec2 &pos, const nsVec2 &size, float angle = 0, const nsColor &c = nsColor( 1, 1, 1, 1 ), uint align = 0 ) const;
	void					Draw( const nsVec2 &pos, const nsVec2 &size, const nsVec2 &center, float angle = 0, const nsColor &c = nsColor( 1, 1, 1, 1 ) ) const;
	
private:
	mutable drawSprite_t	m_spr;
	nsVec2					m_texSize;

private:
	void					UpdateTexCoords( const nsVec2 &texPos, const nsVec2 &texSize );
};

#endif	//_ImageView_H_