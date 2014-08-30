#ifndef _RUNGEKUTTA_H_
#define _RUNGEKUTTA_H_

#include <functional>

//typename F must act as a field.
//It must be possible to add together two Fs to receive an F
// and multiply an F by a double to receive and F.
//typename D must be a callable that returns the derivative,
// when called as
template<typename F>
class RungeKutta{
public:
	RungeKutta(F initial, std::function<F(const F&,double)> derivative,
						 double deltaT, double start_time=0){
		m_current = initial;
		m_der = derivative;
		m_deltaT = deltaT;
		m_time = start_time;
	}
	void Step(){ Step(m_deltaT);}
	void Step(double dT){
		F k1 = m_der(m_current, m_time)*dT;
		F k2 = m_der(m_current + 0.5*k1, m_time + 0.5*dT)*dT;
		F k3 = m_der(m_current + 0.5*k2, m_time + 0.5*dT)*dT;
		F k4 = m_der(m_current + k3, m_time + dT)*dT;
		m_current += (k1 + 2*k2 + 2*k3 + k4) * (1.0/6.0);
		m_time += dT;
	}
	F GetCurrent(){return m_current;}
	double GetTime(){return m_time;}
private:
	F m_current;
	std::function<F(const F&,double)> m_der;
	double m_deltaT;
	double m_time;
};

#endif /* _RUNGEKUTTA_H_ */
