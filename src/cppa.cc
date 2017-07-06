#include <scene.hh>
#include <planet.hh>
#include <SDL/SDL.h>
#include <string>
#include <fstream>
#include <memory>
#include <chrono>
#include <thread>
#include <config.hh>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "CPA";
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
  SDL_Init(SDL_INIT_VIDEO);
  start();
}

static void start()
{
  using namespace std::chrono_literals;
  Scene scene;
  scene.set_sdl_surface(SDL_SetVideoMode(
      WINDOW_WIDTH, WINDOW_HEIGHT,
      0, SDL_HWSURFACE | SDL_DOUBLEBUF));
  SDL_WM_SetCaption(WINDOW_TITLE, 0);
  SDL_Event event;
  scene.add_planet(std::make_shared<Planet>(8000, -200, 0, 0, 1, 0, 0));
  scene.add_planet(std::make_shared<Planet>(8000, 200, 0, 0, -1, 0, 0));
  while (1)
  {
    if(SDL_PollEvent(&event) && event.type == SDL_QUIT)
      SDL_Quit();
    scene.display_planet(800, WINDOW_WIDTH, WINDOW_HEIGHT);
    scene.update();
    scene.print();
    std::this_thread::sleep_for(100ms);
  }
}
