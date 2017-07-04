#include <config.hh>
#include <string>
#include <fstream>
#include <memory>

int main()
{
  std::ifstream("config.txt");
  std::string str;
  struct screen_size* g_stream = new struct screen_size;
  ifs >> str;
  g_stream->screenX = std::stoi(str);
  ifs >> str;
  g_stream->screenY = std::stoi(str);
  ifs >> str;
  g_stream->screenZ = std::stoi(str);
  start();
}

void start()
{
  Scene scene = new Scene();
  scene.add_planet(make_shared<Planet>(5000, 0, 0, 0, 10, 10, 10);
  while (1)
  {
    scene.update();
  }
}
