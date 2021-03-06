#pragma once

#include "Vei2.h"

class Vec2
{
public:
	Vec2() = default;
	Vec2( float x_in,float y_in );
	Vec2 operator+( const Vec2& rhs ) const;
    Vec2 operator+( const Vei2& rhs ) const;
	Vec2& operator+=( const Vec2& rhs );
	Vec2 operator*( float rhs ) const;
	Vec2& operator*=( float rhs );
	Vec2 operator-( const Vec2& rhs ) const;
    Vec2 operator-( const Vei2& rhs ) const;
	Vec2& operator-=( const Vec2& rhs );
    Vec2& operator-=( const Vei2& rhs );
	float GetLength() const;
	float GetLengthSq() const;
    float DotProduct( const Vec2& v ) const;
	Vec2& Normalize();
	Vec2 GetNormalized() const;
	explicit operator Vei2() const;
public:
	float x;
	float y;
};