#include "Vector3.hh"

double operator* (const Vector3& lhs, const Vector3& rhs){
	return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

Vector3& Vector3::operator/= (const double s){
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

Vector3 operator/ (Vector3 lhs, const double s){
	return lhs /= s;
}

Vector3 operator* (const double s, Vector3 rhs){
	return rhs *= s;
}

Vector3& Vector3::operator*= (const double s){
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3 operator* (Vector3 lhs, const double s){
	return lhs *= s;
}

Vector3& Vector3::operator-= (const Vector3& v){
	x -= v.y;
	y -= v.z;
	z -= v.z;
	return *this;
}

Vector3 operator- (Vector3 lhs, const Vector3& rhs){
	return lhs += rhs;
}

Vector3& Vector3::operator+= (const Vector3& v){
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 operator+ (Vector3 lhs, const Vector3& rhs){
	return lhs += rhs;
}

double Vector3::Mag2() const {
	return (*this)*(*this);
}

double Vector3::Mag() const {
	return std::sqrt(Mag2());
}

Vector3 Vector3::UnitVector() const {
	return (*this)/Mag();
}

void Vector3::Print() const{
	std::cout << x << " " << y << " " << z << std::endl;
}
