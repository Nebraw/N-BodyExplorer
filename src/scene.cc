#include <scene.hh>
#include <iostream>
#include <memory>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
/*#include <thread>
#include <mutex>
*/
Scene::Scene()
{
  frames_ = 0;
}

Scene::~Scene()
{

}


void Scene::add_planet(std::shared_ptr<Planet> p)
{

  std::tuple<long, long, long> key = std::make_tuple(p->get_Px(),p->get_Py(),p->get_Pz()); 
  planets_.emplace(key,p);
}

void Scene::check_collision(std::map<std::tuple<long, long, long>,std::shared_ptr<Planet>>& systems,
                            std::tuple<long, long, long>& key,
                            std::shared_ptr<Planet>& p) const
{
  auto search = systems.find(key);
  if (search == systems.end())
    systems.emplace(key,p);
  else
    {
      auto& planet = search->second;
      int masse = p->get_masse() + planet->get_masse();
      planet->set_Vx((planet->get_Vx() * planet->get_masse() + p->get_Vx() * p->get_masse())/masse);
      planet->set_Vy((planet->get_Vy() * planet->get_masse() + p->get_Vy() * p->get_masse())/masse);
      planet->set_Vz((planet->get_Vz() * planet->get_masse() + p->get_Vz() * p->get_masse())/masse);

      planet->set_masse(masse);
    }   
}

void Scene::print() const
{
  std::cout << "\033[32m"<< "frames:" <<frames_ << "\033[m" << std::endl;
  for (auto& i: planets_)
  {
    i.second->print();
  }
}

void Scene::update()
{
  std::map<std::tuple<long, long, long>, std::shared_ptr<Planet>> systems;
  frames_++;
  for (auto& i: planets_)
  {
    long double Ax = 0;
    long double Ay = 0;
    long double Az = 0;
    
    auto& pi = i.second;
    for(auto& j: planets_)
    {
      
      if (i == j)
        continue;
      auto& pj =j.second; 
      long double  Dx = (pj->get_Px() - pi->get_Px());
      long double  Dy = (pj->get_Py() - pi->get_Py());
      long double  Dz = (pj->get_Pz() - pi->get_Pz());

      long double A = G * pj->get_masse()/((Dx * Dx)+(Dy * Dy)+(Dz * Dz));

      long double dp = std::abs(Dx)+std::abs(Dy)+std::abs(Dz);
      Ax = A * (Dx) / dp;
      Ay = A * (Dy) / dp;
      Az = A * (Dz) / dp;
      pi->add_V(Ax, Ay, Az);
    }
    pi->update();
    std::tuple<long, long, long> key = std::make_tuple(pi->get_Px(),pi->get_Py(),pi->get_Pz());
    check_collision(systems, key, pi);
  }
  planets_ = systems;
}

int Scene::display_planet(float scale)
{
  int retcode = 0;
  for(auto& i: planets_)
  {
    int r = (int)(i.second->get_masse() * scale);
    retcode += filledEllipseRGBA(i.second->get_Px(),
        i.second->get_Py(), r, r,
        42, 0, 200, 255);
  }
  return retcode;
}
