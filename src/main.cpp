#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  //Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score Player1: " << game.Player1GetScore() << "\n";
  std::cout << "Score Player2: " << game.Player2GetScore() << "\n";
  std::cout << "Snake Size Player1: " << game.Player1GetSize() << "\n";
  std::cout << "Snake Size Player2: " << game.Player2GetSize() << "\n";
  return 0;
}