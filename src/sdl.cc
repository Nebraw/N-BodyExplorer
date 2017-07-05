/*#include "sdl.hh"
#include <unistd.h>

void line(SDL_Surface* screen, s_point a, s_point b)
{
  drawLine(screen,
      a.x * g_env->echellex,
      a.y * g_env->echelley,
      b.x * g_env->echellex,
      b.y * g_env->echelley,
      a.val, b.val);
}

unsigned long Color(float val)
{
  static float diff2 = (g_env->max - g_env->min) / 2;
  static float mid = (g_env->min + g_env->max) / 2;
  if (val <= g_env->min)
    return 100;
  if (val >= g_env->max)
    return 255 * 65536;
  if (val <= mid)
  {
    float b = 100 + (round(155 * (val - g_env->min) / diff2));
    return b + 256 * (round(255 * (val - g_env->min) / diff2));
  }
  float r = 50 + (round(205 * (val - mid) / diff2));
  return r * 65536 + 256 * (round(255 * (g_env->max - val) / diff2));
}

void PutPixel(SDL_Surface *surface, int x, int y, unsigned long pixel)
{
  int bpp = surface->format->BytesPerPixel;
  unsigned char *p = (unsigned char *)surface->pixels + y * surface->pitch + x * bpp;
  if (bpp==4)
    *(unsigned long*)p = pixel;
}

void drawLine(SDL_Surface* surf,int x1,int y1, int x2,int y2, float val1, float val2)  // Bresenham
{
  unsigned long couleur = Color(val1);
  int x,y;
  int Dx,Dy;
  int xincr,yincr;
  int erreur;
  int i;

  Dx = abs(x2-x1);
  Dy = abs(y2-y1);
  if(x1<x2)
    xincr = 1;
  else
    xincr = -1;
  if(y1<y2)
    yincr = 1;
  else
    yincr = -1;

  x = x1;
  y = y1;
  if(Dx>Dy)
  {
    erreur = Dx/2;
    for(i=0;i<Dx;i++)
    {
      x += xincr;
      erreur += Dy;
      if(erreur>Dx)
      {
        erreur -= Dx;
        y += yincr;
      }
      float rate = (float)(Dx - i) / (float)Dx;
      couleur = Color(val1 * rate + val2 * (1.0 - rate));
      PutPixel(surf,x, y,couleur);
    }
  }
  else
  {
    erreur = Dy/2;
    for(i=0;i<Dy;i++)
    {
      y += yincr;
      erreur += Dx;

      if(erreur>Dy)
      {
        erreur -= Dy;
        x += xincr;
      }
      float rate = (float)(Dy - i) / (float)Dy;
      couleur = Color(val1 * rate + val2 * (1.0 - rate));
      PutPixel(surf,x, y,couleur);
    }
  }
}

static int init()
{
  static bool init = false;
  if (init)
    return 0;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  init = true;
  return 0;
}

int draw(s_point** schape)
{
  if (init())
    return 1;
  SDL_Window *win = SDL_CreateWindow("SIN!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  if (win == nullptr)
  {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr)
  {
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  SDL_Surface *screen = SDL_CreateRGBSurface(0, 640, 480, 32,
      0x00FF0000,
      0x0000FF00,
      0x000000FF,
      0xFF000000);
  SDL_Texture *sdlTexture = SDL_CreateTexture(ren,
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STREAMING,
      640, 480);
  for (int i = 0; i < g_env->tabx - 1; i++)
  {
    for (int j = 0; j < g_env->taby - 1; j++)
    {
      if (schape[i][j].index != -1)
      {
        if (schape[i][j + 1].index != -1)
          line(screen, schape[i][j], schape[i][j + 1]);
        if (schape[i + 1][j].index != -1)
          line(screen, schape[i][j], schape[i + 1][j]);
      }
    }
    if (schape[i][g_env->taby - 1].index != -1 &&
        schape[i + 1][g_env->taby - 1].index != -1)
      line(screen, schape[i - 1][g_env->taby - 1], schape[i + 1][g_env->taby - 1]);
  }
  for (int i = 0; i < g_env->taby - 1; i++)
  {
    if (schape[g_env->tabx - 1][i].index != -1 &&
        schape[g_env->tabx - 1][i + 1].index != -1)
      line(screen, schape[g_env->tabx - 1][i], schape[g_env->tabx - 1][i + 1]);
  }
  SDL_UpdateTexture(sdlTexture, NULL, screen->pixels, screen->pitch);
  SDL_RenderClear(ren);
  SDL_RenderCopy(ren, sdlTexture, NULL, NULL);
  SDL_RenderPresent(ren);
  sleep(g_env->time);
  return 0;
}
*/
