#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Renderer;

//snake predators
enum Predator
{
  NoPredator,
  mangoose,
  eagle,
  badger
};

class Threat {
  public:
    int loc_x, loc_y;
    Predator predatorType;
    Threat();
    Threat(int x, int y, Predator type);
    ~Threat();

  private:

};

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Renderer &renderer, std::size_t target_frame_duration);

  //check for food
  bool FoodCell(int x, int y);

  int Player1GetScore() const;
  int Player2GetScore() const;
  int Player1GetSize() const;
  int Player2GetSize() const;

 private:
  Snake snake;
  Snake snake2;
  SDL_Point food;

  // pointers of Threat class
  std::unique_ptr<Threat> threat;
  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  //std::uniform_int_distribution<size_t> random_type(0, types.size() - 1);
  //std::uniform_int_distribution<int> random_type;

  int scorePlayer1{0};
  int scorePlayer2{0};

  void PlaceFood();
  // placing threat
  void PlaceThreat();
  void Update();
};

#endif