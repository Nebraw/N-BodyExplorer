#pragma once
#include <vector>
#include <planet.hh>
#include <memory>


class Scene
{
public:
  Scene();
  ~Scene();
  void add_planet(std::shared_ptr<Planet> p);
  void destroy_collision();
  void print() const;
  void update();
private:
 static  constexpr long double G = 0.00000000000667408;
  std::vector<std::shared_ptr<Planet>>planets_;
  long frames_;
  
};
