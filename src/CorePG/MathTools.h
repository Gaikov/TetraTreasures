#ifndef _MATH_TOOLS_H_
#define _MATH_TOOLS_H_

#include "headers.h"

#ifndef M_PI
#define	M_PI 3.1415926535897932384626433832795f
#endif

#define M_2PI (2.0f * M_PI)
#define M_PI2 (M_PI / 2.0f)

#include "Vec2.h"

//��������� ������� � ���� � ���� � �������
float	Math_Rad2Deg( float rad );
float	Math_Deg2Rad( float deg );

float	Math_SinUnit( float one );
float	Math_Lerp( float a, float b, float t );
int		Math_Round( float v );
bool	Math_Clamp( float &v, float min, float max );
void	Math_Scale( float &v, float fromStart, float fromEnd, float toStart, float toEnd );
float	Math_Rand( float max );
float	Math_RandRange( float min, float max );
void	Math_RotateVectors( float radAngle, nsVec2 &right, nsVec2 &up );
float	Math_Sign( float value );


//---------------------------------------------------------
// nsMath:
//---------------------------------------------------------
struct nsMath
{
	/* ������� ��������� ����� �� ����� p1, p2, � ����� in, ��������� � out,
    ���������� ���������� �� ������� out ������� �� ��������� ����� p1 ��� p2,
    < 0 - ����� ������ �������. */
	static float			PointOnLine( const nsVec2 &in, nsVec2 &out, const nsVec2 &p1, const nsVec2 &p2 );
	static inline float		Absf( float val );
	static inline double	Absd( double val );

    // ���������� true ���� ����� ����� ������ ���� �� ����� ������������
    static bool				PointInTriangle( const nsVec2 &pt, const nsVec2 &v1, const nsVec2 &v2, const nsVec2 &v3 );
    static inline float		Clamp11( float val );	//����� -1 �� 1

    static bool				IsValidTriangle( int i1, int i2, int i3 ); // ��������� ������� �� ����������

	static inline float		RandAngle();	//���������� ��������� �������� ���� � ��������

	static inline float		Min( float x1, float x2 );
	static inline float		Max( float x1, float x2 );
	static inline void		MinMax( float x1, float x2, float &minRes, float &maxRes );
};

//---------------------------------------------------------
// Math_Rad2Deg: 
//---------------------------------------------------------
inline float Math_Rad2Deg( float rad )
{
	return rad * 180.0f / M_PI;
}

//---------------------------------------------------------
// Math_Deg2Rad: 
//---------------------------------------------------------
inline float Math_Deg2Rad( float deg )
{
	return deg * M_PI / 180.0f;
}

//---------------------------------------------------------
// Math_SinUnit: 
//---------------------------------------------------------
inline float Math_SinUnit( float one )
{
	return sinf( M_PI * (one - 0.5f) ) * 0.5f + 0.5f;
}

//---------------------------------------------------------
// Math_Lerp: 
//---------------------------------------------------------
inline float Math_Lerp( float a, float b, float t )
{
	return a + (b - a) * t;
}

//---------------------------------------------------------
// Math_Round: 
//---------------------------------------------------------
inline int Math_Round( float val )
{
	int		v = (int)val;
	float	rem = val - v;
	if ( rem >= 0.5f ) v++;
	return v;
}

//---------------------------------------------------------
// Math_Clamp: 
//---------------------------------------------------------
inline bool	Math_Clamp( float &v, float min, float max )
{
	if ( v < min )
	{
		v = min;
		return true;
	}
	else if ( v > max )
	{
		v = max;
		return true;
	}
	return false;
}

//---------------------------------------------------------
// Math_Scale: 
//---------------------------------------------------------
inline void Math_Scale( float &v, float fromStart, float fromEnd, float toStart, float toEnd )
{
	v = toStart + (v - fromStart) * (toEnd - toStart) / (fromEnd - fromStart);
}

//---------------------------------------------------------
// Math_Rand: 
//---------------------------------------------------------
inline float Math_Rand( float max )
{
	return float(rand()) * max / float(RAND_MAX);
}

//---------------------------------------------------------
// Math_RandRange: 
//---------------------------------------------------------
inline float Math_RandRange( float min, float max )
{
	if ( min > max )
	{
		float	tmp = min;
		min = max;
		max = tmp;
	}
	
	return min + Math_Rand( 1 ) * (max - min);
}

//---------------------------------------------------------
// Math_RotateVectors:
//---------------------------------------------------------
inline void Math_RotateVectors( float radAngle, nsVec2 &right, nsVec2 &up )
{
	right = nsVec2( cosf( -radAngle ), sinf( -radAngle ) );
	right.GetLeft( up );
}

//---------------------------------------------------------
// Math_Sign:
//---------------------------------------------------------
inline float Math_Sign( float value )
{
	if ( !value ) return 1;
	return value / fabsf( value );
}

//---------------------------------------------------------
// nsMath::Absf:
//---------------------------------------------------------
float nsMath::Absf( float val )
{
	if ( val < 0 ) val = -val;
	return val;
}

//-----------------------------------------------------
// nsMath::Absd:
//-----------------------------------------------------
double nsMath::Absd( double val )
{
	if ( val < 0 ) val = -val;
	return val;
}

//-----------------------------------------------------
// nsMath::Clamp11:
//-----------------------------------------------------
float nsMath::Clamp11( float val )
{
	if ( val > 1 ) val = 1;
    else if ( val < -1 ) val = -1;
    return val;
}

//-----------------------------------------------------
// nsMath::RandAngle:
//-----------------------------------------------------
float nsMath::RandAngle()
{
	return float(rand()) * 2.0f * M_PI / float(RAND_MAX);
}

//-----------------------------------------------------
// nsMath::Min:
//-----------------------------------------------------
float nsMath::Min( float x1, float x2 )
{
	return x1 < x2 ? x1 : x2;
}

//-----------------------------------------------------
// nsMath::Max:
//-----------------------------------------------------
float nsMath::Max( float x1, float x2 )
{
	return x1 > x2 ? x1 : x2;
}

//-----------------------------------------------------
// nsMath::MinMax:
//-----------------------------------------------------
void nsMath::MinMax( float x1, float x2, float &minRes, float &maxRes )
{
	if ( x1 < x2 )
	{
		minRes = x1;
		maxRes = x2;
	}
	else
	{
		minRes = x2;
		maxRes = x1;
	}
}

#endif