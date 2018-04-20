#ifndef _VEC2_H_
#define _VEC2_H_

#include "headers.h"

//---------------------------------------------------------
// nsVec2:
//---------------------------------------------------------
class nsVec2
{
public:
	float	x, y;

	static const nsVec2	null;
public:
	inline nsVec2();
	inline nsVec2( float _x, float _y );
	inline nsVec2( const float v[2] );

    inline operator float*() const;
    inline void operator -= ( const nsVec2& v );
    inline void operator += ( const nsVec2& v );
	inline void operator /= ( float t );
	inline void operator *= ( float t );
	inline void operator *= ( const nsVec2 &v );
	inline nsVec2 operator - ();

    inline float		Length() const;
    inline void			Norm();
	inline void			ToInt();
    inline float		Dot( const nsVec2 &v ) const;
	inline double		DotDouble( const nsVec2 &v );
    inline void 		GetLeft( nsVec2& v ) const;
	inline void 		GetRight( nsVec2& v ) const;
	inline nsVec2		GetLeft() const;
	inline nsVec2		GetRight() const;
	inline void			FromLerp( const nsVec2 &v1, const nsVec2 &v2, float t );
	inline float		DistTo( const nsVec2 &v ) const;
	inline const char*	ToStr() const;
	inline nsVec2&		Invert();
};

//---------------------------------------------------------
// nsVec2::nsVec2:
//---------------------------------------------------------
nsVec2::nsVec2()// : TVec2( 0, 0 )
{
	x = y = 0;
}

//---------------------------------------------------------
// nsVec2::nsVec2:
//---------------------------------------------------------
nsVec2::nsVec2( float _x, float _y )// : TVec2( _x, _y )
{
	x = _x;
	y = _y;
}

//---------------------------------------------------------
// nsVec2::nsVec2:
//---------------------------------------------------------
nsVec2::nsVec2( const float v[2] )// : TVec2( v[0], v[1] )
{
	x = v[0];
	y = v[1];
}

//---------------------------------------------------------
// nsVec2::operator float*:
//---------------------------------------------------------
nsVec2::operator float*() const
{
	return (float*)&x;
}

//---------------------------------------------------------
// nsVec2::operator -=:
//---------------------------------------------------------
void nsVec2::operator -= ( const nsVec2& v )
{
	x -= v.x;
    y -= v.y;
}

//---------------------------------------------------------
// nsVec2::operator +=:
//---------------------------------------------------------
void nsVec2::operator += ( const nsVec2& v )
{
	x += v.x;
    y += v.y;
}

//---------------------------------------------------------
// nsVec2::operator /=:
//---------------------------------------------------------
void nsVec2::operator /= ( float t )
{
	x /= t;
    y /= t;
}

//---------------------------------------------------------
// nsVec2::operator *=:
//---------------------------------------------------------
void nsVec2::operator *= ( float t )
{
	x *= t;
	y *= t;
}

//---------------------------------------------------------
// nsVec2::operator *= :
//---------------------------------------------------------
void nsVec2::operator *= ( const nsVec2 &v )
{
	x *= v.x;
	y *= v.y;
}

//---------------------------------------------------------
// nsVec2::operator - : 
//---------------------------------------------------------
nsVec2 nsVec2::operator - ()
{
	return nsVec2( -x, -y );
}

//---------------------------------------------------------
// nsVec2::Length:
//---------------------------------------------------------
float nsVec2::Length() const
{
	return (float)sqrt( x * x + y * y );
}

//---------------------------------------------------------
// nsVec2::Norm:
//---------------------------------------------------------
void nsVec2::Norm()
{
	float	len = Length();
    x /= len;
    y /= len;
}

//---------------------------------------------------------
// nsVec2::ToInt:
//---------------------------------------------------------
void nsVec2::ToInt()
{
	x = (float)int(x);
	y = (float)int(y);
}

//---------------------------------------------------------
// nsVec2::Dot:
//---------------------------------------------------------
float nsVec2::Dot( const nsVec2 &v ) const
{
	return x * v.x + y * v.y;
}

//-----------------------------------------------------
// nsVec2::DotDouble:
//-----------------------------------------------------
double nsVec2::DotDouble( const nsVec2 &v )
{
	return double(x) * v.x + double(y) * v.y;
}

//---------------------------------------------------------
// nsVec2::GetLeft
//---------------------------------------------------------
void nsVec2::GetLeft( nsVec2& v ) const
{
	v.x = -y;
    v.y = x;
}

//---------------------------------------------------------
// nsVec2::GetRight
//---------------------------------------------------------
void nsVec2::GetRight( nsVec2& v ) const
{
	v.x = y;
	v.y = -x;
}

//---------------------------------------------------------
// nsVec2::GetLeft:
//---------------------------------------------------------
nsVec2 nsVec2::GetLeft() const
{
	nsVec2	v;
	GetLeft( v );
	return v;
}

//---------------------------------------------------------
// nsVec2::GetRight:
//---------------------------------------------------------
nsVec2 nsVec2::GetRight() const
{
	nsVec2	v;
	GetRight( v );
	return v;
}

//---------------------------------------------------------
// nsVec2::FromLerp:
//---------------------------------------------------------
void nsVec2::FromLerp( const nsVec2 &v1, const nsVec2 &v2, float t )
{
	x = v1.x + (v2.x - v1.x) * t;
	y = v1.y + (v2.y - v1.y) * t;
}

//---------------------------------------------------------
// nsVec2::DistTo:
//---------------------------------------------------------
float nsVec2::DistTo( const nsVec2 &v ) const
{
	float	distX = v.x - x;
	float	distY = v.y - y;
	return (float)sqrt( distX * distX + distY * distY );
}

//---------------------------------------------------------
// nsVec2::ToStr:
//---------------------------------------------------------
const char*	nsVec2::ToStr() const
{
	static char str[64];
	sprintf( str, "[%f %f]", x, y );
	return str;
}

//---------------------------------------------------------
// nsVec2::Invert:
//---------------------------------------------------------
nsVec2&	nsVec2::Invert()
{
	x = -x;
	y = -y;
	return *this;
}

//---------------------------------------------------------
// nsVec2 operator + :
//---------------------------------------------------------
inline nsVec2 operator + ( const nsVec2 &v1, const nsVec2 &v2 )
{
	return nsVec2( v1.x + v2.x, v1.y + v2.y );
}

//---------------------------------------------------------
// inline nsVec2 operator *: 
//---------------------------------------------------------
inline nsVec2 operator * ( const nsVec2 &v1, const nsVec2 &v2 )
{
	return nsVec2( v1.x * v2.x, v1.y * v2.y );
}

//---------------------------------------------------------
// nsVec2 operator -:
//---------------------------------------------------------
inline nsVec2 operator - ( const nsVec2 &v1, const nsVec2 &v2 )
{
	return nsVec2( v1.x - v2.x, v1.y - v2.y );
}

//---------------------------------------------------------
// nsVec2 operator *:
//---------------------------------------------------------
inline nsVec2 operator * ( const nsVec2 &v, float t )
{
	return nsVec2( v.x * t, v.y * t );
}

//-----------------------------------------------------
// nsVec2 operator /:
//-----------------------------------------------------
inline nsVec2 operator / ( const nsVec2 &v, float t )
{
	return nsVec2( v.x / t, v.y / t );
}

#endif