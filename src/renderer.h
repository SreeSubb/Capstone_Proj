#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <mutex>
#include "SDL.h"
#include "snake.h"
#include "game.h"

class Threat;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  //Added 2nd snake & threat pointer
  void Render(Snake const snake, Snake const snake2, SDL_Point const &food, std::unique_ptr<Threat> const &threat);
  //void Render(Snake const snake, Snake const snake2, SDL_Point const &food);
  void UpdateWindowTitle(int score1, int score2, int fps);
  void RenderThreat(std::unique_ptr<Threat> const &threat, SDL_Rect &block); 

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  std::mutex _mutex;
};

#endif