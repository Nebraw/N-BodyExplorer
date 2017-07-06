#pragma once
#include <vector>
#include <planet.hh>
#include <memory>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

class Scene
{
public:
  Scene();
  ~Scene();
  void add_planet(std::shared_ptr<Planet> p);
  void print() const;
  void update();
  int display_planet(float scale, int x, int y);
  void set_sdl_surface(SDL_Surface* surf)
  {
    this->surf = surf;
  }
private:
  void check_collision(std::map<std::tuple<long, long, long>, std::shared_ptr<Planet>>& systems,
                       std::tuple<long, long, long>& key,
                       std::shared_ptr<Planet> &p) const;
 static  constexpr long double G = 0.00000000000667408;
  std::map<std::tuple<long,long,long>,std::shared_ptr<Planet>>planets_;
  long frames_;
  SDL_Surface *surf;
};
