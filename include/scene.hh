#pragma once
#include <vector>
#include <planet.hh>
#include <memory>
#include <map>

class Scene
{
public:
  Scene();
  ~Scene();
  void add_planet(std::shared_ptr<Planet> p);
  void print() const;
  void update();
private:
  void check_collision(std::map<std::tuple<long, long, long>, std::shared_ptr<Planet>>& systems,
                       std::tuple<long, long, long>& key,
                       std::shared_ptr<Planet> &p) const;
 static  constexpr long double G = 0.00000000000667408;
  std::map<std::tuple<long,long,long>,std::shared_ptr<Planet>>planets_;
  long frames_;
  
};
