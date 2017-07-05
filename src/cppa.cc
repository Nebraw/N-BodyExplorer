#include <scene.hh>
#include <planet.hh>

#include <string>
#include <fstream>
#include <memory>
#include <chrono>
#include <thread>
#include <config.hh>

static void start();
 struct screen_size* g_screen;
int main()
{
  std::ifstream ifs("config.txt");
  std::string str;
  g_screen = new struct screen_size;
  ifs >> str;
  g_screen->screenX = std::stoi(str);
  ifs >> str;
  g_screen->screenY = std::stoi(str);
  ifs >> str;
  g_screen->screenZ = std::stoi(str);
  start();
}

static void start()
{
  using namespace std::chrono_literals;
  Scene scene;
  scene.add_planet(std::make_shared<Planet>(8000, -200, 0, 0, 1, 0, 0));
  scene.add_planet(std::make_shared<Planet>(8000, 200, 0, 0, -1, 0, 0));
  while (1)
  {
    scene.update();
    scene.print();
    std::this_thread::sleep_for(100ms);
  }
}
