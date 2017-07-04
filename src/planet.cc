#include <planet.hh>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <cmath>
#include <config.hh>

Planet::Planet()
{
  std::default_random_engine generator;

  std::uniform_int_distribution<int> distributionmasse(1000,10000);
  masse_ = distributionmasse(generator);
  
  std::uniform_real_distribution<double> distributionX(0,g_screen->screenX);
  px_ =  distributionX(generator);
  
  std::uniform_real_distribution<double> distributionY(0,g_screen->screenY);
  py_ =  distributionY(generator);

  std::uniform_real_distribution<double> distributionZ(0,g_screen->screenZ);
  pz_ = distributionZ(generator);
  
  id_ = planet_id();
}

Planet::Planet(int masse,
               double px, double py, double pz,
               double vx, double vy, double vz)
{
  masse_ = masse; 
  px_ = px;
  py_ = py;
  pz_ = pz;

  vx_ = vx;
  vy_ = vy;
  vz_ = vz;
  
  id_ = planet_id();
}


void Planet::print() const
{
  std::cout <<"planete id:"<< id_ << std::endl
            << "posX: " << px_
            << ", posY: " << py_
            << ", posZ: " << pz_ << std::endl;              
}

int Planet::get_masse() const
{
  return masse_;
}
