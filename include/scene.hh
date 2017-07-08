#pragma once

#include <planet.hh>

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <vector>

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
  void gravite(const long double mult);

  void calcule(std::pair<const std::tuple<long, long, long>, std::shared_ptr<Planet>>& i,
               std::map<std::tuple<long, long, long>, std::shared_ptr<Planet>>& systems);
private:
  void check_collision(std::map<std::tuple<long, long, long>, std::shared_ptr<Planet>>& systems,
                       std::tuple<long, long, long>& key,
                       std::shared_ptr<Planet> &p);
 static  constexpr long double G = 0.00000000000667408;
  long double mult_;
  std::map<std::tuple<long,long,long>,std::shared_ptr<Planet>>planets_;
  long frames_;
  SDL_Surface *surf;
  
  boost::asio::io_service ioservice_;
  boost::asio::io_service::work ioservicework_;
  boost::thread_group threadpool_;

  std::mutex all_;
  std::mutex abs_;

  std::atomic<int> count_;
  std::condition_variable cv_;
};
