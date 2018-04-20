// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Font.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "Font.h"
#include "FontManager.h"
#include "Align.h"
#include "StrTools.h"
#include "log.h"
#include "ParseFile.h"

//---------------------------------------------------------
// nsFont::nsFont:
//---------------------------------------------------------
nsFont::nsFont() :
	m_refCount( 1 ),
	avg_height( 0 )
{
	memset( ch, 0, sizeof(ch) );
}

//---------------------------------------------------------
// nsFont::~nsFont:
//---------------------------------------------------------
nsFont::~nsFont()
{

}

//---------------------------------------------------------
// nsFont::Load: 
//---------------------------------------------------------
bool nsFont::Load( const char *fileName )
{
	m_fileName = fileName;
	m_fileName.ConvFileName();
	if ( !StrCheck( fileName ) ) return false;
	
	LogPrintf( PRN_ALL, "loading font: '%s'\n", fileName );
	
	nsParseFile		pf;
	script_state_t	*ss = pf.BeginFile( fileName );
	if ( !ss )
	{
		LogPrintf( PRN_ALL, "WARNING: can't parsing font!\n" );
		return false;
	}

	float ver = ps_get_f( ss, "version" );
	
	//-------------------------------------------
	if ( ps_block_begin( ss, "textures" ) 
		&& ps_var_begin( ss, "tex" ) )
	{
		do
		{
			str	texName = ps_var_str( ss );
			TTextureRef	tex = TTexture::Get( texName );
			if ( tex )
				m_texList.push_back( tex );
		}
		while ( ps_var_next( ss ) );
		ps_block_end( ss );
	}
	
	if ( !m_texList.size() )
	{
		LogPrintf( PRN_ALL, "WARNING: font textures not loaded!\n" );
		return false;
	}
	
	//-------------------------------------------
	int	i = 0;
	avg_height = 0;
	float	min_h = 0;
	float	max_h = 0;
	if ( ps_block_begin( ss, "chars_data" ) 
		&& ps_block_begin( ss, "char" ) )
	{
		bool	init_max = true;

		do
		{
			int	code;
			ps_var_begin( ss, "code" );
			code = (int)ps_var_f( ss );
			
			int	tex_id;
			ps_var_begin( ss, "tex_id" );
			tex_id = (int)ps_var_f( ss );
			TTextureRef	tex;
			if ( tex_id >= 0 && tex_id < (int)m_texList.size() )
				tex = m_texList[tex_id];
			
			if ( code >= 0 && code < MAX_CHARS && tex )
			{
				ch[code].tex = tex;
				
				ps_var_begin( ss, "coord" );
				ps_var_2f( ss, ch[code].v.texPos );
				
				ps_var_begin( ss, "size" );
				ps_var_2f( ss, ch[code].v.outSize );
				
				ps_var_begin( ss, "offs" );
				ps_var_2f( ss, ch[code].v.outOffs );

				ch[code].v.step = ps_get_f( ss, "step", 0 );
				
				int	w = 1, h = 1;
				if ( ch[code].tex )
				{
					w = ch[code].tex->GetWidth();
					h = ch[code].tex->GetHeight();
				}
				
				ch[code].v.texSize.x = ch[code].v.outSize.x / float(w);
				ch[code].v.texSize.y = ch[code].v.outSize.y / float(h);
				ch[code].v.texPos.x /= float(w);
				ch[code].v.texPos.y /= float(h);

				if ( !ver )
				{
					ch[code].v.step = ch[code].v.outOffs.x + ch[code].v.outSize.x;
					ch[code].v.outOffs.x = 0;
					ch[code].v.outOffs.y += ch[code].v.outSize.y;
				}

				float minV = -ch[code].v.outOffs.y;
				float maxV = ch[code].v.outSize.y - ch[code].v.outOffs.y;
				
				if ( init_max )
				{
					min_h = minV;
					max_h = maxV;
					init_max = false;
				}
				else
				{
					if ( min_h > minV ) min_h = minV;
					if ( max_h < maxV ) max_h = maxV;
				}
				
				i++;
			}
		}
		while ( ps_block_next( ss ) && i < MAX_CHARS );
	}
	
	if ( !i )
	{
		LogPrintf( PRN_ALL, "WARNING: no chars data present!\n" );
		return false;
	}

	avg_height = max_h - min_h;
	m_baseLine = max_h;
	return true;
}

//---------------------------------------------------------
// nsFont::Create:
//---------------------------------------------------------
nsFont::sp_t nsFont::Create( const char *fileName )
{
	nsFont *f = new nsFont;
	if ( !f->Load( fileName ) )
	{
		delete f;
		return 0;
	}
	
	return f;
}

//---------------------------------------------------------
// nsFont::Draw:
//---------------------------------------------------------
void nsFont::Draw( const char *str, const nsVec2 &pos, const nsVec2 &scale, const nsColor &c, int len )
{
	if ( !str || !m_texList.size() ) return;

	TRenderer	*ren = TRenderer::GetInstance();
	
	ren->SetTexture( m_texList[0] );
	TTextureRef	prev_tex = m_texList[0];

	if ( !len ) len = (int)strlen( str );

	nsFontRender	*r = g_fntMgr->GetFontRender();
	r->DrawBegin( pos );

	TColor32 color = c.ToColor32();

	while ( *str && len )
	{
		unsigned char	chr = (unsigned char)*str;

		charDesc_t	*c = &ch[chr];
		if ( c->tex )
		{
			if ( *str != 32 )
			{
				if ( prev_tex != c->tex )
				{
					ren->SetTexture( c->tex );
					prev_tex = c->tex;
					r->DrawFlush();
				}

				r->AddChar( c->v, scale, color );
			}
			else
				r->AddStep( c->v.step * scale.x );
		}

		str++;
		len--;
	}

	r->DrawFlush();
}

//---------------------------------------------------------
// nsFont::DrawFX:
//---------------------------------------------------------
void nsFont::DrawFX( const char *str, const nsVec2 &pos, const nsVec2 &scale, const nsColor &color, int len, IFontCallback *fcb )
{
	if ( !str || !m_texList.size() ) return;

	TRenderer	*ren = TRenderer::GetInstance();

	ren->SetTexture( m_texList[0] );
	TTextureRef	prev_tex = m_texList[0];

	if ( !len ) len = (int)strlen( str );

	nsFontRender	*r = g_fntMgr->GetFontRender();
	r->DrawBegin( pos );

	charDrawParams_t	dp;
	int					count = 0;

	while ( *str && len )
	{
		unsigned char	chr = (unsigned char)*str;

		charDesc_t	*c = &ch[chr];
		if ( c->tex )
		{
			if ( *str != 32 )
			{
				if ( prev_tex != c->tex )
				{
					ren->SetTexture( c->tex );
					prev_tex = c->tex;
					r->DrawFlush();
				}

				dp.color = color;
				dp.angle = 0;
				dp.offs = nsVec2( 0, 0 );
				dp.scale = nsVec2( 1, 1 );
				if ( fcb ) fcb->OnChar( count, dp );
				r->AddCharFX( c->v, scale, dp );
			}
			else
				r->AddStep( c->v.step * scale.x );
		}

		str++;
		len--;
		count ++;
	}

	r->DrawFlush();
}

//---------------------------------------------------------
// nsFont::GetSize:
//---------------------------------------------------------
void nsFont::GetSize( const char *str, nsVec2 &size, int len )
{
	size.x = size.y = 0;
	if ( !str ) return;
	if ( !len ) len = (int)strlen( str );

	while ( *str && len )
	{
		charDesc_t	*c = &ch[(unsigned char)*str];
		size.x += c->v.step;
		str++;
		len--;
	}

	size[1] = avg_height;
}

//---------------------------------------------------------
// nsFont::GetCharView:
//---------------------------------------------------------
const charView_t* nsFont::GetCharView( uchar code )
{
	if ( ch[code].tex ) return &ch[code].v;
	return 0;
}

//---------------------------------------------------------
// Font_DrawAligned:
//---------------------------------------------------------
void Font_DrawAligned( nsFont *font, const char *str, const nsVec2 &pos, uint align, const nsVec2 &scale, const nsColor &c, int len )
{
	if ( !font ) return;

	nsVec2	size;
	font->GetSize( str, size, len );
	size *= scale;

	nsVec2	offs = Align_CalcSizeOffs( size, align );

	float	base = 0;
	uint	vert = Align_GetVert( align );
	if ( vert == ALIGN_VERT_CENTER )
		base = font->GetBase() * scale.y;// * 0.5f;
	else if ( vert == ALIGN_VERT_TOP )
		base = font->GetBase() * scale.y;
	
	nsVec2	p( pos.x - offs.x, pos.y + offs.y - base );

	p.x = ceilf( p.x );
	p.y = ceilf( p.y );
	font->Draw( str, p, scale, c, len );
}