#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <iostream>
#include <complex>

struct Vector3{
	Vector3(){ x=y=z = 0;}
	Vector3(double x, double y, double z) :
		x(x), y(y), z(z) { }
	Vector3(const Vector3& v) :
		x(v.x), y(v.y), z(v.z) { }

	Vector3& operator+= (const Vector3& v);
	Vector3& operator-= (const Vector3& v);
	Vector3& operator*= (const double s);
	Vector3& operator/= (const double s);

	double Mag2() const;
	double Mag() const;
	Vector3 UnitVector() const;

	void Print() const;

	double x,y,z;
};

double operator* (const Vector3& lhs, const Vector3& rhs);
Vector3 operator* (const double s, Vector3 rhs);
Vector3 operator* (Vector3 lhs, const double s);
Vector3 operator- (Vector3 lhs, const Vector3& rhs);
Vector3 operator+ (Vector3 lhs, const Vector3& rhs);

#endif /* _VECTOR3_H_ */
