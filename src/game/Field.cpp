// Copyright (c) 2005-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Field.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "Field.h"
#include "Treasures.h"

nsField *g_field = 0;

//---------------------------------------------------------
// nsField::nsField:
//---------------------------------------------------------
nsField::nsField() :
	m_valid( true )
{
	Clear();
	m_sndBreak = Sound_Load( "sounds/fig_break.ogg" );
	m_sndPlace = Sound_Load( "sounds/fig_place.ogg" );
}

//---------------------------------------------------------
// nsField::~nsField:
//---------------------------------------------------------
nsField::~nsField()
{

}

//---------------------------------------------------------
// nsField::Init:
//---------------------------------------------------------
bool nsField::Init()
{
	if ( !g_field )
	{
		g_field = new nsField;
		if ( !g_field->m_valid )
		{
			delete g_field;
			g_field = 0;
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------
// nsField::Release:
//---------------------------------------------------------
void nsField::Release()
{
	if ( g_field )
	{
		delete g_field;
		g_field = 0;
	}
}

//---------------------------------------------------------
// nsFieldView::FillField:
//---------------------------------------------------------
void nsField::FillField( int percent )
{
	for ( int y = 1; y < FIELD_HEIGHT - 1; ++y )
		for ( int x = 1; x < FIELD_WIDTH - 1; ++x )
		{

		}
}

//---------------------------------------------------------
// nsField::Clear:
//---------------------------------------------------------
void nsField::Clear()
{
	for ( int y = 0; y < FIELD_HEIGHT; ++y )
		for ( int x = 0; x < FIELD_WIDTH; ++x )
		{
			cell_t	&cell = Map( x, y );
			cell.type = -1;
			cell.placed = false;
		}
	UncheckAll();
}

//---------------------------------------------------------
// nsFieldView::MouseClick:
//---------------------------------------------------------
int nsField::MouseClick( float x, float y )
{

	return 0;
}

//---------------------------------------------------------
// nsFieldView::Loop:
//---------------------------------------------------------
void nsField::Loop( float time )
{
}

//---------------------------------------------------------
// nsFieldView::Draw:
//---------------------------------------------------------
void nsField::Draw()
{
	/*int	width = FIELD_WIDTH * FIELD_CELL;
	int height = FIELD_HEIGHT * FIELD_CELL;

	float	x = FIELD_X;
	float	y = FIELD_Y;

	drawSprite_t	spr;
	spr.pos = nsVec2( x, y );
	spr.size = nsVec2( (float)width, (float)height );
	spr.color = nsColor::green;
	spr.color.a = 0.2f;
	RX_DrawSprite( spr );

	nsVec2	pos( x, y );
	for ( int i = 0; i < FIELD_WIDTH + 1; i++ )
	{
		RX_DrawLine( pos, nsVec2( pos.x, pos.y + height ), nsColor::green );
		pos.x += FIELD_CELL;
	}

	pos = nsVec2( x, y );
	for ( int i = 0; i < FIELD_HEIGHT + 1; i++ )
	{
		RX_DrawLine( pos, nsVec2( pos.x + width, pos.y ), nsColor::green );
		pos.y += FIELD_CELL;
	}//*/

	float	x = FIELD_X;
	float	y = FIELD_Y;

	for ( int y = 0; y < FIELD_HEIGHT; ++y )
		for ( int x = 0; x < FIELD_WIDTH; ++x )
		{
			cell_t	&cell = Map( x, y );
			if ( cell.type >= 0 )
			{
				const nsImageView &img = g_figBase->GetTypeView( cell.type );
				nsVec2	pos;
				pos.x = Field_PosX( x );
				pos.y = Field_PosY( y );
				img.Draw( pos, nsVec2( FIELD_CELL, FIELD_CELL ) );
			}
		}
}

//---------------------------------------------------------
// nsFieldView::CheckType:
//---------------------------------------------------------
nsField::matchType_t nsField::CheckType( int cellX, int cellY, int type )
{
	if ( cellX < 0 || cellX >= FIELD_WIDTH ) return TYPE_NONE;
	if ( cellY < 0 || cellY >= FIELD_HEIGHT ) return TYPE_NONE;

	cell_t	&cell = m_map[cellY][cellX];
	if ( cell.type < 0 ) return TYPE_NONE;
	
	if ( !cell.check )
	{
		cell.check = true;
		cell.del = (cell.type == type);
		if ( cell.del )
			return cell.placed ? TYPE_PLACED : TYPE_MATCH;
		else
			return TYPE_NONE;
	}
	return TYPE_NONE;
}

//---------------------------------------------------------
// nsFieldView::CheckCount:
//---------------------------------------------------------
nsField::count_t nsField::CheckCount( int cellX, int cellY, int type )
{
	count_t	c;
	c.found = 0;
	c.placed = 0;
	matchType_t match = CheckType( cellX, cellY, type );
	if ( !match )
		return c;
	else if ( match == TYPE_MATCH )
		c.found ++;
	else if ( match == TYPE_PLACED )
		c.placed ++;

	c += CheckCount( cellX + 1, cellY, type );
	c += CheckCount( cellX - 1, cellY, type );
	c += CheckCount( cellX, cellY + 1, type );
	c += CheckCount( cellX, cellY - 1, type );
	return c;
}

//---------------------------------------------------------
// nsField::CheckStep:
//---------------------------------------------------------
bool nsField::CheckStep( nsFigureView *fv )
{
	int currRot = fv->GetRotation();

	for ( int rot = 0; rot < 4; ++rot )
	{
		fv->SetRotation( rot );
		for ( int x = 0; x < FIELD_WIDTH - fv->GetWidth() + 1; ++x )
			for ( int y = 0; y < FIELD_HEIGHT - fv->GetHeight() + 1; ++y )
			{
				if ( CheckPlace( x, y, fv ) )
				{
					fv->SetRotation( currRot );
					return true;
				}
			}
	}

	fv->SetRotation( currRot );
	return false;
}

//---------------------------------------------------------
// nsField::FigurePlace:
//---------------------------------------------------------
void nsField::FigurePlace( int cellX, int cellY, nsFigureView *fv )
{
	for ( int x = 0; x < fv->GetWidth(); ++x )
		for ( int y = 0; y < fv->GetHeight(); ++y )
		{
			cell_t &cell = Map( x + cellX, y + cellY );
			figCell_t &fc = fv->GetCell( x, y );
			if ( fc.cell != ' ' )
			{
				cell.type = fc.type;
				cell.placed = true;
			}
		}

	int	mul = 0;
	{
		for ( int x = 0; x < fv->GetWidth(); ++x )
			for ( int y = 0; y < fv->GetHeight(); ++y )
			{
				cell_t &cell = Map( x + cellX, y + cellY );
				figCell_t &fc = fv->GetCell( x, y );
				if ( fc.cell != ' ' )
				{
					count_t c = CheckCount( x + cellX, y + cellY, fc.type );
					if ( c.found + c.placed >= 3 && c.found > 0 )
					{
						mul ++;
						DestroyMarked();
					}
					UncheckAll();
				}
			}
	}

	if ( mul )
		Sound_Play( m_sndBreak );
	else
		Sound_Play( m_sndPlace );

	g_tres->SetCompo( mul );
	UncheckPlaced();
}

//---------------------------------------------------------
// nsField::CheckPlace:
//---------------------------------------------------------
bool nsField::CheckPlace( int cellX, int cellY, nsFigureView *fv )
{
	for ( int x = 0; x < fv->GetWidth(); ++x )
		for ( int y = 0; y < fv->GetHeight(); ++y )
		{
			cell_t &cell = Map( x + cellX, y + cellY );
			figCell_t &fc = fv->GetCell( x, y );
			if ( fc.cell != ' ' )
			{
				if ( cell.type >= 0 )
					return false;
			}
		}
	return true;
}

//---------------------------------------------------------
// nsFieldView::DestroyCell:
//---------------------------------------------------------
void nsField::DestroyMarked()
{
	g_tres->BreakStart( 10, 20 );

	for ( int y = 0; y < FIELD_HEIGHT; ++y )
		for ( int x = 0; x < FIELD_WIDTH; ++x )
		{
			cell_t	&cell = Map( x, y );
			if ( cell.del )
			{
				g_tres->BreakBox( x, y, cell.type );
				cell.type = -1;
				cell.del = false;
				cell.placed = false;
				cell.check = false;
			}
		}
}

//---------------------------------------------------------
// nsFieldView::UncheckAll:
//---------------------------------------------------------
void nsField::UncheckAll()
{
	for ( int y = 0; y < FIELD_HEIGHT; ++y )
		for ( int x = 0; x < FIELD_WIDTH; ++x )
		{
			m_map[y][x].check = false;
			m_map[y][x].del = false;
		}
}

//---------------------------------------------------------
// nsField::UncheckPlaced:
//---------------------------------------------------------
void nsField::UncheckPlaced()
{
	for ( int y = 0; y < FIELD_HEIGHT; ++y )
		for ( int x = 0; x < FIELD_WIDTH; ++x )
			m_map[y][x].placed = false;
}
