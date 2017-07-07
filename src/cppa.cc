#include <scene.hh>
#include <planet.hh>
#include <config.hh>

#include <chrono>
#include <cstdlib>
#include <memory>
#include <thread>

#include <fstream>
#include <iostream>
#include <sstream>

#include <SDL/SDL.h>
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "CPA";
static void start(int argc, char** argv);
static void parse(Scene &scene, int& argc, char** argv);
struct screen_size* g_screen;
int main(int argc, char** argv)
{
  if (argc == 1)
    {
      std::cout << "No file provided" << std::endl;
      return 1;
    }
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
  start(argc, argv);
}

static void start(int argc, char** argv)
{
  using namespace std::chrono_literals;
  Scene scene; 
  scene.set_sdl_surface(SDL_SetVideoMode
                        (
                         g_screen->screenX,  g_screen->screenY,
                         0, SDL_HWSURFACE | SDL_DOUBLEBUF));
  SDL_Event event;  parse(scene, argc, argv);
  while (1)
  {
    if(SDL_PollEvent(&event) && event.type == SDL_QUIT)
      SDL_Quit();
    scene.update();
    scene.display_planet(800, WINDOW_WIDTH, WINDOW_HEIGHT);
    scene.print();
    std::this_thread::sleep_for(100ms);
  }
}

static void parse(Scene &scene, int& argc, char** argv)
{
  for (int i = 0; i < argc; i++)
    {
      try
        {
      std::ifstream fs(argv[i]);
      std::string line;
      for (;std::getline(fs, line);)
        {
          std::stringstream lines(line);
          std::string val;
          lines >> val;
          int masse = std::stoi(val.c_str());
          lines >> val;
          double X  = std::atof(val.c_str());
          lines >> val;
          double Y = std::atof(val.c_str());
          lines >> val;
          double Z = std::atof(val.c_str());
          lines >> val;
          double Vx = std::atof(val.c_str());
          lines >> val;
          double Vy = std::atof(val.c_str());
          lines >> val;
          double Vz = std::atof(val.c_str());
          
          scene.add_planet(std::make_shared<Planet>(masse, X, Y, Z, Vx, Vy, Vz));
         }
        }  
      catch(std::exception)
        {
        std::cerr << "Cannot parse the file " << std::endl;
        }
    }
}
