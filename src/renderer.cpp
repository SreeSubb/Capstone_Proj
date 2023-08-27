#include "renderer.h"
#include <iostream>
#include <string>
#include <memory>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

//Adding 2nd snake
void Renderer::Render(Snake const snake, Snake const snake2, SDL_Point const &food, std::unique_ptr<Threat> const &threat) {
//void Renderer::Render(Snake const snake, Snake const snake2, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render 1st snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render 2nd snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xBF, 0x90, 0x00, 0xFF);
  for (SDL_Point const &point : snake2.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  } // 

  // Render 1st snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render 2nd snake's head
  block.x = static_cast<int>(snake2.head_x) * block.w;
  block.y = static_cast<int>(snake2.head_y) * block.h;
  if (snake2.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x3D, 0x85, 0xC6, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  //Render Threat
  RenderThreat(threat, block);

  // Render threat , unique lock
  /* std::unique_lock<std::mutex> uLock(_mutex);
  switch (threat->predatorType)
  {
  case Predator::mangoose:
    SDL_SetRenderDrawColor(sdl_renderer, 0xF3, 0xF3, 0x26, 0xFF);
    break;
  case Predator::eagle:
    SDL_SetRenderDrawColor(sdl_renderer, 0xFC, 0x4B, 0x00, 0xFF);
    break;
  case Predator::badger:
    SDL_SetRenderDrawColor(sdl_renderer, 0xD4, 0x12, 0x44, 0xFF);
    break;
  default:
    break;
  }
  uLock.unlock(); 

  block.x = threat->loc_x * block.w;
  block.y = threat->loc_y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block); */

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}
//add 2nd snake and score, get the player snake score printed.
//Rendering threats
void Renderer::RenderThreat(std::unique_ptr<Threat> const &threat, SDL_Rect &block) {

  std::unique_lock<std::mutex> uLock(_mutex);
  // Render threat
  switch (threat->predatorType)
  {
  case Predator::mangoose:
    SDL_SetRenderDrawColor(sdl_renderer, 0xF3, 0xF3, 0x26, 0xFF);
    break;
  case Predator::eagle:
    SDL_SetRenderDrawColor(sdl_renderer, 0xFC, 0x4B, 0x00, 0xFF);
    break;
  case Predator::badger:
    SDL_SetRenderDrawColor(sdl_renderer, 0xD4, 0x12, 0x44, 0xFF);
    break;
  default:
    break;
  }
  uLock.unlock(); 
 // SDL_SetRenderDrawColor(sdl_renderer, 0xFC, 0x4B, 0x00, 0xFF);
  block.x = threat->loc_x * block.w;
  block.y = threat->loc_y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
} 

void Renderer::UpdateWindowTitle(int score1, int score2, int fps) {
  std::string title{"1st Player Score: " + std::to_string(score1) + " & " 
                  + "2ndt Player Score: " + std::to_string(score2) + " FPS: " 
                  + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
