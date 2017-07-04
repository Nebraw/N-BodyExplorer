#pragma once
#include <vector>
#include <planet.hh>
#include <memory>


class Scene
{
public:
  Scene();
  ~Scene();
  void add_planet( share_pointer<Planet> p);
  void destroy_collision();
  void print() const;
  void update();
private:
  constexpr double G = 0.00000000000667408;
  std::vector<share_pointer<Planet>>planets_;
  long frames_;
  
};
