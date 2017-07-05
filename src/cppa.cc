#include <scene.hh>
#include <planet.hh>

#include <string>
#include <fstream>
#include <memory>
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
  Scene scene;
  scene.add_planet(std::make_shared<Planet>(5000, 0, 0, 0, 10, 10, 10));
  while (1)
  {
    scene.update();
  }
}
