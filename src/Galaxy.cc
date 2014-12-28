#include "Galaxy.hh"

#include "RungeKutta.hh"

GalaxyContents::GalaxyContents() { }

GalaxyContents::GalaxyContents(std::vector<Sphere> contents) :
  contents(contents) { }

GalaxyContents GalaxyContents::operator*(double scale){
  std::vector<Sphere> scaled_contents;
  scaled_contents.reserve(contents.size());
  std::transform(contents.begin(), contents.end(),
                 std::back_inserter(scaled_contents),
                 [scale](Sphere sp){
                   return Sphere{sp.location*scale, sp.velocity*scale}; } );
  return GalaxyContents(scaled_contents);
}

GalaxyContents GalaxyContents::operator+ (const GalaxyContents& other){
  if(contents.size() != other.contents.size()){
    throw new IncompatibleSizesException("Can't add galaxies of different sizes");
  }

  std::vector<Sphere> summed_contents;
  summed_contents.reserve(contents.size());
  std::transform(contents.begin(), contents.end(), other.contents.begin(),
                 std::back_inserter(summed_contents),
                 [](Sphere s1, Sphere s2){
                   return Sphere{s1.location+s2.location, s1.velocity+s2.velocity}; } );
  return GalaxyContents(summed_contents);
}

GalaxyContents GalaxyDisplacementDerivative(const GalaxyContents& gal, double time){
  std::vector<Sphere> new_contents;
  new_contents.reserve(gal.contents.size());
  for(auto sp : gal.contents){
    new_contents.push_back({sp.velocity, {0,0,0}});
  }
  return GalaxyContents(new_contents);
}

GalaxyContents GalaxyGravityDerivative(const GalaxyContents& gal, double time){
  std::vector<Sphere> new_contents;
  new_contents.reserve(gal.contents.size());
  for(const auto& sp : gal.contents){
    Sphere der = {sp.velocity, {0,0,0}};
    for(const auto& other : gal.contents){
      if(&sp != &other){
        GVector<3> disp = other.location - sp.location;
        double dist2 = disp.Mag2();
        disp = disp.UnitVector();
        double grav_magnitude = 1/dist2;

        der.velocity += grav_magnitude*disp;
      }
    }
    new_contents.push_back(der);
  }
  return GalaxyContents(new_contents);
}

Galaxy::Galaxy() : time(0) { }

void Galaxy::AddSphere(Sphere sp){
  state.contents.push_back(sp);
}

void Galaxy::Step(double dT){
  RungeKuttaStep(state, time, GalaxyGravityDerivative, dT);
}

std::ostream& operator<<(std::ostream& out, const Galaxy& gal){
  out << "---------------" << std::endl;
  out << gal.state.contents.size() << " spheres" << std::endl;
  out << "t = " << gal.time << std::endl;
  for(unsigned int i=0; i<gal.state.contents.size(); i++){
    const Sphere& sp = gal.state.contents[i];
    out << i << ": " << sp.location << ", " << sp.velocity << std::endl;
  }
  out << "---------------";
}
