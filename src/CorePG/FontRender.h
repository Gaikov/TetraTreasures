// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FontRender.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FontRender_H_
#define	_FontRender_H_

#include "comm_types.h"
#include "Vec2.h"
#include "color.h"
#include "RenPatchBuffer.h"

//---------------------------------------------------------
// charView_t:
//---------------------------------------------------------
struct charView_t
{
	nsVec2	texPos;		//������� ������� �� ��������
	nsVec2	texSize;	//������ ������� �� ��������
	nsVec2	outSize;	//������ ������� ��� ������
	nsVec2	outOffs;	//�������� �� ������� ��� ������
	float	step;		//��� ����� ������
};

//---------------------------------------------------------
// charDrawParams_t:
//---------------------------------------------------------
struct charDrawParams_t
{
	nsVec2	scale;
	nsVec2	offs;
	float	angle;
	nsColor	color;
};

//---------------------------------------------------------
// nsFontRender:
//---------------------------------------------------------
class nsFontRender : public nsRenPatchBuffer
{
public:
	nsFontRender( uint reserveChars );

	void		DrawBegin( const nsVec2 &startPos );
	void		ResetPos( const nsVec2 &pos );
	void		DrawFlush();

	void		AddChar( const charView_t &cv, const nsVec2 &scale, TColor32 color );
	void		AddCharFX( const charView_t &cv, const nsVec2 &scale, const charDrawParams_t &p );
	void		AddStep( float step );

private:
	nsVec2		m_currPos;
	uint		m_countChars;	//������� ���-�� �������� � ������
};

#endif	//_FontRender_H_