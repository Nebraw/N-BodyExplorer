#pragma once

#include <cmath>

class Planet
{
public:
  Planet();
  Planet(double px, double py, double pz,
         double vx, double vy, double vz);

  void print() const;
private:

  static const int planet_id();

  int masse_;
  unsigned id_;
  
  double px_;
  double py_;
  double pz_;

  double vx_ = 0;
  double vy_ = 0;
  double vz_ = 0;
};
