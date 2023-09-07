#include <iostream>
#include <fstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  
  //user information collection
  std::ofstream InputOutput("Player_data.txt", std::ios::app);        // to append file std::ios:app
  std::string playerName1;
  std::cout << "Enter 1st Player Name:" << std::endl;
  std::cin >> playerName1;
  std::string playerName2;
  std::cout << "Enter 2nd Player Name:" << std::endl;
  std::cin >> playerName2;
  InputOutput << playerName1 << std::endl << playerName2 << std::endl;
  
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Game game(kGridWidth, kGridHeight);
  game.Run(renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score Player1: " << game.Player1GetScore() << "\n";
  std::cout << "Score Player2: " << game.Player2GetScore() << "\n";
  std::cout << "Snake Size Player1: " << game.Player1GetSize() << "\n";
  std::cout << "Snake Size Player2: " << game.Player2GetSize() << "\n";

  //storing the score in user information file
  InputOutput << game.Player1GetScore() << std::endl << game.Player2GetScore() << std::endl;
  InputOutput.close();

  return 0;
}