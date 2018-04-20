// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file RenAux.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_RenAux_H_
#define	_RenAux_H_

#include "comm_types.h"
#include "Vec2.h"
#include "color.h"
#include "BBox2.h"
#include <pf/texture.h>

void		RX_DrawFPS( float x, float y, float frameTime );
void		RX_BuildSpriteVerts( nsVec2 v[4], const nsVec2 &pos, const nsVec2 &size, const nsVec2 &center = nsVec2( 0, 0 ), float angle = 0 );

struct drawSprite_t
{
	inline drawSprite_t() :
		angle( 0 ),
		useTex( false ),
		tex2( 1, 1 )
	{}

	TTextureRef	tex;
	nsVec2		pos;
	nsVec2		center;
	nsVec2		size;
	nsColor		color;
	float		angle;

	bool		useTex;
	nsVec2		tex1, tex2;	//верхний левый, правый нижний (текстурные координаты)
};

void RX_DrawSprite( const drawSprite_t &desc );

//void RX_DrawStrip( ITexture *tex, const nsVec2 &pos1, const nsVec2 &pos2, float width, const nsColor &color = nsColor::white, bool wrapTex = false );

//вершины против часовой стрелки
void RX_DrawQuad( TTextureRef tex, TLitVert v[4] );

void RX_DrawBBox( const nsVec2 &pos, const nsBBox2 &box, const nsColor &color = nsColor::white );
void RX_DrawRect( const TRect &r, const nsColor &color = nsColor::white );
void RX_DrawLine( const nsVec2 &v1, const nsVec2 &v2, const nsColor &color = nsColor::white );
//void RX_DrawLine( const nsVec3 &v1, const nsVec3 &v2, const nsColor &color = nsColor::white );
void RX_DrawCross( const nsVec2 &v, float size, const nsColor &c = nsColor::white );
void RX_DrawLinedSprite( TTextureRef tex, const nsVec2 &pos1, const nsVec2 &pos2, float width, const nsColor &c, float texOffs = 0 );

void RX_DrawLight( TTextureRef tex, const nsVec2 &pos, float size, const nsColor &c = nsColor::white );

/*void RX_IndicesStrip( IVertexBuffer *vb, int vertCount );//*/

//void RX_DrawSprite( ITexture *tex, const nsVec2 &pos, const nsVec2 &size, const nsColor &color = nsColor::white, nsVec2 &warping =  );

#endif //_RenAux_H_