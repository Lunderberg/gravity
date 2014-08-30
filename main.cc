#include <iostream>

#include "RungeKutta.hh"
#include "Vector3.hh"

using std::cout;
using std::endl;

Vector3 deriv(const Vector3& v, double t){
	return Vector3(-v.x, v.y, t);
}

int main(){
	auto rk = RungeKutta<Vector3>({1,1,0},deriv,0.1);
	for(int i=0; i<100; i++){
		cout << rk.GetTime() << " "
				 << rk.GetCurrent().x << " "
				 << rk.GetCurrent().y << " "
				 << rk.GetCurrent().z << endl;
		rk.Step();
	}
}
