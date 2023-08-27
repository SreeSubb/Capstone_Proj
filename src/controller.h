#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  //getter/setter to handle two players
  Controller(SDL_Keycode up, SDL_Keycode dn, SDL_Keycode lt, SDL_Keycode rt);

  void HandleInput(bool &running, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
  
  SDL_Keycode _Up;
  SDL_Keycode _Dn;
  SDL_Keycode _Rt;
  SDL_Keycode _Lt;
};

#endif