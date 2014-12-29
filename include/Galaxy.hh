#ifndef _GALAXY_H_
#define _GALAXY_H_

#include <algorithm>
#include <iterator>
#include <ostream>
#include <vector>

#include "GVector.hh"
#include "GravityExceptions.hh"

struct Sphere{
  Sphere(GVector<3> location, GVector<3> velocity) :
    location(location), velocity(velocity) { }

  GVector<3> location;
  GVector<3> velocity;
};

struct GalaxyContents{
  GalaxyContents();
  GalaxyContents(std::vector<Sphere> contents);

  GalaxyContents operator* (double scale);
  GalaxyContents operator+ (const GalaxyContents& other);

  std::vector<Sphere> contents;
};

class Galaxy{
public:
  Galaxy();

  void AddSphere(Sphere sp);
  void Step(double dT);

  const GalaxyContents& GetState(){return state;}

  friend std::ostream& operator<<(std::ostream& out, const Galaxy& gal);

private:
  GalaxyContents state;
  double time;
};

std::ostream& operator<<(std::ostream& out, const Galaxy& gal);

#endif /* _GALAXY_H_ */
