// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file RenAux.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "RenAux.h"
#include "StrTools.h"
#include "MathTools.h"
#include <pf/textgraphic.h>

static uint16_t g_quadIdx[] = { 0, 1, 2, 0, 2, 3 };

//---------------------------------------------------------
// RX_Vec2ToVec3: 
//---------------------------------------------------------
inline void RX_Vec2ToVec3( TVec3 &r, const nsVec2 &v )
{
	r.x = v.x;
	r.y = v.y;
	r.z = 0;
}

//---------------------------------------------------------
// RX_DrawFPS: 
//---------------------------------------------------------
void RX_DrawFPS( float x, float y, float frameTime )
{
	static	float	fps = 0;
	static	int		frames = 0;
	static	float	time = 0;
	frames ++;
	time += frameTime;
	if ( frames > 10 )
	{
		fps = float(frames / time);
		frames = 0;
		time = 0;
	}

	static TTextGraphic	*t = 0;
	if ( !t )
	{
		t = TTextGraphic::Create( "fps", 100, 100, 
			TTextGraphic::kHAlignLeft | TTextGraphic::kVAlignTop,
		"fonts/arial.mvec", 20, TColor( 1, 1, 1, 1 ) );
	}
			
	//float	p[2] = { x, y };
	TRect	rect;
	rect = TRect::FromXYWH( (uint32_t)x, (uint32_t)y, 100, 100 );
	str		s;
	s.format( "%.2f fps", fps );
	t->SetText( s );
	
	t->Draw( rect, 1, 0, 1 );
}

//---------------------------------------------------------
// RX_BuildSpriteVerts: 
//---------------------------------------------------------
void RX_BuildSpriteVerts( nsVec2 v[4], const nsVec2 &pos, const nsVec2 &size, const nsVec2 &center, float angle )
{
	if ( angle )
	{
		nsVec2	axisRight, axisDown;
		Math_RotateVectors( angle, axisRight, axisDown );

		nsVec2	right = axisRight * size.x;
		nsVec2	up = axisDown * size.y;

		nsVec2	offs = axisRight * center.x + axisDown * center.y;
		
		v[0] = pos - offs;
		v[1] = pos + up - offs;
		v[2] = pos + right + up - offs;
		v[3] = pos + right - offs;
	}
	else
	{
		v[0] = pos - center;
		v[1] = nsVec2( pos.x, pos.y + size.y ) - center;
		v[2] = nsVec2( pos.x + size.x, pos.y + size.y ) - center;
		v[3] = nsVec2( pos.x + size.x, pos.y ) - center;
	}
}

//---------------------------------------------------------
// RX_DrawSprite: 
//---------------------------------------------------------
void RX_DrawSprite( const drawSprite_t &desc )
{
	TRenderer *r = TRenderer::GetInstance();
	r->SetTexture( desc.tex );

	TLitVert	v[4];
	nsVec2		vert[4];
	word		idx[] = { 0, 1, 2, 0, 2, 3 };

	//vbVertex_t *v = g_sprBuff->GetWriteVertices();

	RX_BuildSpriteVerts( vert, desc.pos, desc.size, desc.center, desc.angle );

	TColor32	c = desc.color.ToColor32();

	for ( int i = 0; i < 4; ++i )
	{
		RX_Vec2ToVec3( v[i].pos, vert[i] );
		v[i].color = c;
	}
	
	if ( desc.useTex )
	{
		v[0].uv.x = desc.tex1.x;
		v[0].uv.y = desc.tex1.y;

		v[1].uv.x = desc.tex1.x;
		v[1].uv.y = desc.tex2.y;

		v[2].uv.x = desc.tex2.x;
		v[2].uv.y = desc.tex2.y;

		v[3].uv.x = desc.tex2.x;
		v[3].uv.y = desc.tex1.y;
	}
	else
	{
		v[0].uv.x = 0;
		v[0].uv.y = 0;

		v[1].uv.x = 0;
		v[1].uv.y = 1;

		v[2].uv.x = 1;
		v[2].uv.y = 1;

		v[3].uv.x = 1;
		v[3].uv.y = 0;
	}

	TVertexSet	vs( v, 4 );

	//r->DrawIndexedVertices( TRenderer::kDrawTriangles, vs, g_quadIdx, 6 );
	r->DrawVertices( TRenderer::kDrawTriFan, vs );
}

//---------------------------------------------------------
// RX_DrawRect:
//---------------------------------------------------------
void RX_DrawRect( const TRect &r, const nsColor &color )
{
	nsVec2	v1( (float)r.mX1, (float)r.mY1 );
	nsVec2	v2( (float)r.mX2, (float)r.mY2 );

	RX_DrawLine( v1, nsVec2( v1.x, v2.y ), color );
	RX_DrawLine( v2, nsVec2( v1.x, v2.y ), color );

	RX_DrawLine( v1, nsVec2( v2.x, v1.y ), color );
	RX_DrawLine( v2, nsVec2( v2.x, v1.y ), color );
}

//---------------------------------------------------------
// RX_DrawLine: 
//---------------------------------------------------------
void RX_DrawLine( const nsVec2 &v1, const nsVec2 &v2, const nsColor &color )
{
	TRenderer	*r = TRenderer::GetInstance();
	
	r->SetTexture();

	TColor32	c = color.ToColor32();

	TLitVert	v[2];
	v[0].pos = TVec3( v1.x, v1.y, 0 );
	v[0].color = c;
	
	v[1].pos = TVec3( v2.x, v2.y, 0 );
	v[1].color = c;

	TVertexSet	vs( v, 2 );

	uint16_t	i[] = { 0, 1 };

	//r->DrawIndexedVertices( TRenderer::kDrawLines, vs, i, 2 );
	r->DrawVertices( TRenderer::kDrawLineStrip, vs );
}

//---------------------------------------------------------
// RX_DrawSpriteLined: 
// отрисовака от позиции pos1 вниз к позиции pos2
// расположение текстуры вертикальное от pos1 к pos2
//---------------------------------------------------------
/*void RX_DrawStrip( ITexture *tex, const nsVec2 &pos1, const nsVec2 &pos2, float width, const nsColor &color, bool wrapTex )
{
	g_renDev->TextureBind( tex );

	nsVec2	right, down;

	down = pos2 - pos1;

	
	down.GetLeft( right );

	float	texY = 1;
	right.Norm();
	right *= width;

	float	tv = 1;
	if ( wrapTex )
		tv = down.Length() / width;

	nsVec2		pos = pos1 - right * 0.5f;
	vbVertex_t	*v = g_sprBuff->GetWriteVertices();
	v[0].c = color.ToARGB();
	
	RX_Vec2ToVec3( v[0].v, pos + down );
	RX_Vec2ToVec3( v[1].v, pos + down + right );
	RX_Vec2ToVec3( v[2].v, pos + right );
	RX_Vec2ToVec3( v[3].v, pos );

	v[0].tu = 0;
	v[0].tv = tv;

	v[1].tu = 1;
	v[1].tv = tv;

	v[2].tu = 1;
	v[2].tv = 0;

	v[3].tu = 0;
	v[3].tv = 0;

	g_renDev->VerticesDraw( g_sprBuff );
}//*/

//---------------------------------------------------------
// RX_DrawQuad: 
//---------------------------------------------------------
void RX_DrawQuad( TTextureRef tex, TLitVert v[4] )
{
	TRenderer *r = TRenderer::GetInstance();

	//r->SetTexture();
	r->SetTexture( tex );

	TVertexSet	vs( v, 4 );
	r->DrawVertices( TRenderer::kDrawTriFan, vs );
	//r->DrawIndexedVertices( TRenderer::kDrawTriangles, vs, g_quadIdx, 6 );
}

//---------------------------------------------------------
// RX_DrawLine: 
//---------------------------------------------------------
/*void RX_DrawLine( const nsVec3 &v1, const nsVec3 &v2, const nsColor &color )
{
	g_renDev->TextureBind( 0 );

	vbVertex_t	*v = g_lineBuff->GetWriteVertices();

	v[0].c = v[1].c = color.ToARGB();

	v[0].v = v1;
	v[1].v = v2;

	g_renDev->VerticesDraw( g_lineBuff );
}//*/

//---------------------------------------------------------
// RX_DrawCross:
//---------------------------------------------------------
void RX_DrawCross( const nsVec2 &v, float size, const nsColor &c )
{
	float	s = size * 0.5f;
	RX_DrawLine( nsVec2( v.x - s, v.y ), nsVec2( v.x + s, v.y ), c );
	RX_DrawLine( nsVec2( v.x, v.y - s), nsVec2( v.x, v.y + s ), c );
}

//---------------------------------------------------------
// RX_DrawLinedSprite:
//---------------------------------------------------------
void RX_DrawLinedSprite( TTextureRef tex, const nsVec2 &pos1, const nsVec2 &pos2, float width, const nsColor &c, float texOffs )
{
	float	height = 0;
	if ( tex ) height = (float)tex->GetHeight();

	nsVec2	down = pos2 - pos1;
	nsVec2	right;
	down.GetRight( right );

	float	length = down.Length();
	right /= length;
	height = length / height;

	nsVec2	pos = pos1 - right * width * 0.5f;

	right *= width;

	TLitVert	v[4];
	TColor32	color = c.ToColor32();
	for ( int i = 0; i < 4; ++i )
		v[i].color = color;


	v[0].pos = TVec3( pos.x, pos.y, 0 );
	v[0].uv.x = 0;
	v[0].uv.y = -texOffs;

	RX_Vec2ToVec3( v[1].pos, pos + down );
	v[1].uv.x = 0;
	v[1].uv.y = height - texOffs;

	RX_Vec2ToVec3( v[2].pos, pos + down + right );
	v[2].uv.x = 1;
	v[2].uv.y = height - texOffs;

	RX_Vec2ToVec3( v[3].pos, pos + right );
	v[3].uv.x = 1;
	v[3].uv.y = -texOffs;

	TRenderer	*r = TRenderer::GetInstance();
	r->SetTextureMapMode( TRenderer::kMapClamp, TRenderer::kMapWrap );
	r->SetTexture( tex );
	r->DrawVertices( TRenderer::kDrawTriFan, TVertexSet( v, 4 ) );
	r->SetTextureMapMode( TRenderer::kMapClamp, TRenderer::kMapClamp );
}

//---------------------------------------------------------
// RX_DrawLight:
//---------------------------------------------------------
void RX_DrawLight( TTextureRef tex, const nsVec2 &pos, float size, const nsColor &c )
{
	TRenderer *r = TRenderer::GetInstance();
	
	drawSprite_t	spr;
	uint32_t		width, height;
	bool			fs;
	TPlatform::GetInstance()->GetDisplay( &width, &height, &fs );

	float	w = float(width);
	float	h = float(height);

	float	s = size * 0.5f;
	
	float	texSize = 1.0f / size;
	float	texWidth = w / size;
	float	texHeight = h / size;

	float	x = (pos.x - s) / size;
	float	y = (pos.y - s) / size;

	spr.tex1.x = -x;
	spr.tex1.y = -y;
	spr.tex2.x = texWidth - (x + texSize);
	spr.tex2.y = texHeight - (y + texSize);

	
	spr.tex = tex;
	spr.size = nsVec2( w, h );
	spr.color = c;
	spr.useTex = true;

	
	RX_DrawSprite( spr );
	/*nsBBox2	box( -s, -s, s, s );
	RX_DrawBBox( pos, box );//*/
	//r->SetTextureMapMode( TRenderer::kMapWrap, TRenderer::kMapWrap );
	//r->SetTextureMapMode( TRenderer::kMapClamp, TRenderer::kMapClamp );
}

//---------------------------------------------------------
// RX_DrawBBox: 
//---------------------------------------------------------
void RX_DrawBBox( const nsVec2 &pos, const nsBBox2 &box, const nsColor &color )
{
	nsVec2	min = pos + box.m_min;
	nsVec2	max = pos + box.m_max;

	RX_DrawLine( min, nsVec2( min.x, max.y ), color );
	RX_DrawLine( min, nsVec2( max.x, min.y ), color );

	RX_DrawLine( nsVec2( min.x, max.y ), max, color );
	RX_DrawLine( nsVec2( max.x, min.y ), max, color );
}

//---------------------------------------------------------
// RX_IndicesStrip: 
//---------------------------------------------------------
/*void RX_IndicesStrip( IVertexBuffer *vb, int vertCount )
{
	assert( vb );

	word	*idx = vb->GetWriteIndices();
	for ( int i = 0; i < vertCount; ++i )
		idx[i] = i;
}//*/

