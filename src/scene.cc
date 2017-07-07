#include <scene.hh>
#include <iostream>
#include <memory>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <thread>
#include <mutex>

Scene::Scene():
  ioservicework_(ioservice_)
{
  frames_ = 0;
  for (int i =0; i < 10; i++)
    threadpool_.create_thread(boost::bind(&boost::asio::io_service::run, &ioservice_));
}

Scene::~Scene()
{
  ioservice_.stop();
}


void Scene::add_planet(std::shared_ptr<Planet> p)
{

  std::tuple<long, long, long> key = std::make_tuple(p->get_Px(),p->get_Py(),p->get_Pz()); 
  planets_.emplace(key,p);
}

void Scene::check_collision(std::map<std::tuple<long, long, long>,std::shared_ptr<Planet>>& systems,
                            std::tuple<long, long, long>& key,
                            std::shared_ptr<Planet>& p)
{
  std::lock_guard<std::mutex> guard(abs_);
  //  guard.lock();
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
  //  guard.unlock();
}

void Scene::print() const
{
  std::cout << "\033[32m"<< "frames:" <<frames_ << "\033[m" << std::endl;
  for (auto& i: planets_)
  {
    i.second->print();
  }
}

void Scene::calcule(std::pair<const std::tuple<long, long, long>, std::shared_ptr<Planet>>& i,
                    std::map<std::tuple<long, long, long>, std::shared_ptr<Planet>>& systems)
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
  count_--;
  if (count_ == 0)
    cv_.notify_all();
}

void Scene::update()
{
   
  std::map<std::tuple<long, long, long>, std::shared_ptr<Planet>> systems;
  frames_++;
  std::unique_lock<std::mutex> locked (all_);
  count_ = planets_.size();
  for (auto& i: planets_)
  {
    ioservice_.post(boost::bind(&Scene::calcule,boost::ref(*this), i, systems));
  }
  while (count_ != 0)
    cv_.wait(locked);

  planets_ = systems;
}

int Scene::display_planet(float scale, int x, int y)
{
  int retcode = 0;
  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 50, 50, 50));
  int component = 255 / planets_.size();
  printf("planet component %d\n", component);
  int c_r = 0;
  int c_g = 0;
  int c_b = 0;
  for(auto& i: planets_)
  {
    c_r = c_b == c_g ? component : c_r;
    c_g = c_r == c_b ? component : c_g;
    c_b = c_r == c_g ? component : c_b;
    component += component;
    int r = i.second->get_masse() / scale;
    retcode += filledEllipseRGBA(surf, i.second->get_Px() + x/2,
        i.second->get_Py() + y/2, r, r,
        c_r, c_g, c_b, 255);
  }
  retcode += SDL_Flip(surf);
  return retcode;
}
