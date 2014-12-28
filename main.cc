#include <iostream>
using std::cout;
using std::endl;

#include "Galaxy.hh"

int main(){
  Galaxy g;
  g.AddSphere({{1, 0,0},{0,1,0}});
  g.AddSphere({{-1,0,0},{0,-1,0}});

  cout << g << endl;
  for(int i=0; i<5; i++){
    g.Step(1.0);
    cout << g << endl;
  }
}
