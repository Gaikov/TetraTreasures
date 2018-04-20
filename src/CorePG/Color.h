// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Color.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Color_H_
#define	_Color_H_

#include <pf/pftypes.h>
#include "MathTools.h"

class nsColor : public TColor
{
public:
	static const nsColor	white;
	static const nsColor	yellow;
	static const nsColor	red;
	static const nsColor	green;
	static const nsColor	blue;
	static const nsColor	gray;

public:
	nsColor();
	nsColor( float _r, float _g, float _b, float _a = 1 );

	operator float* ();
	void		FromLerp( const nsColor &a, const nsColor &b, float t );
	TColor32	ToColor32() const;
};

//---------------------------------------------------------
// nsColor::nsColor:
//---------------------------------------------------------
inline nsColor::nsColor() : TColor( 1, 1, 1, 1 )
{
}

//---------------------------------------------------------
// nsColor::nsColor:
//---------------------------------------------------------
inline nsColor::nsColor( float _r, float _g, float _b, float _a /*= 1 */ ) :
TColor( _r, _g, _b, _a )
{

}

//---------------------------------------------------------
// nsColor::operator float* :
//---------------------------------------------------------
inline nsColor::operator float* ()
{
	return &r;
}

//---------------------------------------------------------
// nsColor::FromLerp:
//---------------------------------------------------------
inline void	nsColor::FromLerp( const nsColor &c1, const nsColor &c2, float t )
{
	r = Math_Lerp( c1.r, c2.r, t );
	g = Math_Lerp( c1.g, c2.g, t );
	b = Math_Lerp( c1.b, c2.b, t );
	a = Math_Lerp( c1.a, c2.a, t );
}

//---------------------------------------------------------
// nsColor::ToColor32:
//---------------------------------------------------------
inline TColor32 nsColor::ToColor32() const
{
	TColor32	c;
	c.SetRed( uint8_t(255.0f * r) );
	c.SetGreen( uint8_t(255.0f * g) );
	c.SetBlue( uint8_t(255.0f * b) );
	c.SetAlpha( uint8_t(255.0f * a) );
	return c;
}

#endif	//_Color_H_