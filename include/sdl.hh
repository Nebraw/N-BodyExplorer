#pragma once

#include "main.hh"

#include "point.hh"
#include <SDL2/SDL.h>

unsigned long Color(float val);
void PutPixel(SDL_Surface *surface, int x, int y, unsigned long pixel);
void drawLine(SDL_Surface* surf,int x1,int y1, int x2,int y2, float val1, float val2);
int draw(s_point** schape);
void line(s_point a, s_point b);

extern struct conf* g_env;

#include <iostream>
