// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Field.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Field_H_
#define	_Field_H_

#include "common.h"
#include "FieldParams.h"
#include "FigureView.h"

//---------------------------------------------------------
// nsField:
//---------------------------------------------------------
class nsField
{
public:
	static bool Init();
	static void Release();

	void		FillField( int percent );
	void		Clear();
	bool		CheckStep( nsFigureView *fv );
	void		FigurePlace( int cellX, int cellY, nsFigureView *fv );
	bool		CheckPlace( int cellX, int cellY, nsFigureView *fv );
	int			MouseClick( float x, float y );

	const nsBBox2&	GetBox() { return m_box; }

	void	Loop( float time );
	void	Draw();

protected:
	struct cell_t 
	{
		bool		check;
		bool		placed;
		bool		del;
		int			type;
	};

	enum matchType_t
	{
		TYPE_NONE,
		TYPE_PLACED,
		TYPE_MATCH
	};

	struct count_t
	{
		int	found;
		int placed;

		void operator += ( const count_t &c )
		{
			found += c.found;
			placed += c.placed;
		}
	};

protected:
	cell_t		m_map[FIELD_HEIGHT][FIELD_WIDTH];
	nsBBox2		m_box;

protected:
	nsField();
	~nsField();

	
	matchType_t	CheckType( int cellX, int cellY, int type );
	count_t		CheckCount( int cellX, int cellY, int type );
	void		DestroyMarked();
	void		UncheckAll();
	void		UncheckPlaced();
	
	inline cell_t&	Map( int x, int y )
	{
		return m_map[y][x];
	}

private:
	bool		m_valid;
	TSoundRef	m_sndBreak;
	TSoundRef	m_sndPlace;
};

extern nsField *g_field;

#endif	//_Field_H_